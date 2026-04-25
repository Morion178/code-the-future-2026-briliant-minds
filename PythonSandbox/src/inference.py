import torch
import joblib
import numpy as np
import serial
import time
import math
import socket
from model import EngineTwinModel

# --- 1. INITIALIZE MODEL & SCALERS ---
model = EngineTwinModel(input_dim=14, hidden_dim=256, output_dim=4)
model.load_state_dict(torch.load("../models/engine_twin.pth", weights_only=True))
model.eval()

scaler_X = joblib.load("../models/scaler_X.pkl")
scaler_y = joblib.load("../models/scaler_y.pkl")

# --- 2. SERIAL SETUP ---
SERIAL_PORT = 'COM15'
BAUD_RATE = 115200
# --- 2.1 UDP SETUP ---
UDP_IP = "127.0.0.1"  # "127.0.0.1" if Java is on the same PC
UDP_PORT = 5005       # Pick a port (ensure it's the same in Java)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

GEAR_RATIOS = {
    0: 0.0,    # Neutral
    1: 3.5,    # 1st Gear
    2: 2.1,    # 2nd Gear
    3: 1.5,    # 3rd Gear
    4: 1.1,    # 4th Gear
    5: 0.9,    # 5th Gear
    6: 0.7,     # 6th Gear (Overdrive)
    7: 0.6
}
FINAL_DRIVE = 3.42  # Differential ratio
WHEEL_CIRCUMFERENCE = 2.0  # Meters (approx 18-inch wheel + tire)


def send_to_java(rpm, speed, honk, gear):
    """
    Java expects: RPM, Speed, Temp, CO2, L/100, Honk (6 parts)
    """
    # 1. Simple math for extra 'realism' in the dashboard
    sim_temp = 85.0 + (rpm / 2000.0)  # Temp rises slightly with RPM
    sim_co2 = 120 + (rpm / 10.0)  # CO2 rises with RPM
    sim_l100 = 0.0 if speed < 5 else (rpm / 1200.0)  # Fuel consumption logic

    # 2. Construct the 6-part string
    # Format: RPM, Speed, Temp, CO2, L/100, Honk
    data_list = [
        round(rpm, 1),
        round(speed, 1),
        round(sim_temp, 1),
        round(sim_co2, 0),
        round(sim_l100, 1),
        int(honk),
        int(gear)
    ]

    message = ",".join(map(str, data_list))
    sock.sendto(message.encode(), (UDP_IP, UDP_PORT))

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    print(f"Connected to ESP32 on {SERIAL_PORT}")
except Exception as e:
    print(f"Serial Error: {e}")
    ser = None

# --- 3. STATE & EXPONENTIAL CONFIG ---
# Corrected to 14 features (removed leading 0)
initial_state = np.array([
    3.549, 1.889, 7.428, 5.227, 1192.769, 3.057, 11.72, 24.901,
    0.46, 196.089, 14.356, 1.08, 1.047, 15.385
])
history_buffer = [initial_state.copy() for _ in range(5)]

# Exponential Variables
t_progress = 0.0  # The 0.0 to 1.0 incrementer
k_val = 2.5  # Curvature (Higher = more exponential/aggressive)
inc_speed = 0.02  # Speed of rev up (t increases by this much per step)
dec_speed = 0.015  # Speed of rev down (t decreases by this much per step)


def run_simulation_step(new_tps, gear, is_braking=False):
    global history_buffer
    current_row = history_buffer[-1].copy()

    # 1. TPS & Braking Logic
    active_tps = 1.889 if is_braking else new_tps
    current_row[1] = active_tps

    # 2. Prepare AI Input
    history_buffer.append(current_row)
    if len(history_buffer) > 5: history_buffer.pop(0)

    history_array = np.array(history_buffer)
    history_scaled = scaler_X.transform(history_array)
    input_tensor = torch.FloatTensor(history_scaled).unsqueeze(0)

    with torch.no_grad():
        prediction_scaled = model(input_tensor)

    prediction_real = scaler_y.inverse_transform(prediction_scaled.numpy())[0]
    ai_rpm = prediction_real[0]

    # 3. Dynamic RPM Calculation (The "Feel")
    if active_tps <= 2.0:
        res_rpm = (ai_rpm * 0.1) + (1192.0 * 0.9)
    else:
        weight = (active_tps - 2.0) / (4.8 - 2.0)
        target_rpm = 1192.0 + (weight * (9000.0 - 1192.0))
        res_rpm = (ai_rpm * 0.2) + (target_rpm * 0.8)

    # 4. GEAR PHYSICS: Calculate Speed from RPM
    # Formula: Speed (km/h) = (RPM * Wheel_Circ * 60) / (Gear_Ratio * Final_Drive * 1000)
    ratio = GEAR_RATIOS.get(gear, 0.0)

    if ratio > 0 and not is_braking:
        # Calculate theoretical speed based on current engine RPM
        calculated_speed = (res_rpm * WHEEL_CIRCUMFERENCE * 60) / (ratio * FINAL_DRIVE * 1000)
        # Blend with AI speed for "momentum" effect
        final_speed = (calculated_speed * 0.7) + (prediction_real[1] * 0.3)
    elif is_braking:
        final_speed = max(0, current_row[7] * 0.85)
    else:
        final_speed = 0  # Neutral or stopped

    # 5. Sanity Checks & Buffer Update
    res_rpm = max(800.0, min(9500.0, res_rpm))

    history_buffer[-1][4] = res_rpm
    history_buffer[-1][7] = final_speed

    return [res_rpm, prediction_real[2], prediction_real[3], final_speed]


# --- 4. REAL-TIME LOOP ---
print(f"{'Btn':<4} | {'Brk':<4} | {'Gear':<4} | {'T-Prog':<8} | {'Exp-TPS':<7} | {'RPM':<8}")
print("-" * 65)

# Initialize persistent states
btn_pressed = 0
brake_input = False
current_gear = 0
honk_active = False

# Initialize persistent states before the loop

try:
    while True:
        start_time = time.time()

        # 1. READ AND DECODE SERIAL
        if ser and ser.in_waiting > 0:

            if ser.in_waiting > 100:  # If more than ~5-10 lines are backed up
                ser.reset_input_buffer()
            try:
                # Read raw bytes first to see if ANYTHING is coming in
                raw_data = ser.readline()
                line = raw_data.decode('utf-8', errors='ignore').strip()

                # DEBUG: Uncomment the line below to see EVERY raw packet


                if line and "," in line:
                    parts = line.split(',')
                    if len(parts) >= 4:
                        btn_pressed = int(parts[0])
                        brake_input = bool(int(parts[1]))
                        honk_active = bool(int(parts[2]))
                        current_gear = int(parts[3])
                        print(f"DEBUG RAW: {btn_pressed, brake_input, honk_active, current_gear}")
                        # Successful read! Let's mark it
                        # print("Data Received!")

            except Exception as e:
                print(f"Decode Error: {e}")
                continue

        # 2. PHYSICS & AI LOGIC (Always runs)
        # Update t_progress based on the last known btn_pressed state
        if btn_pressed == 1:
            t_progress += inc_speed
        else:
            t_progress -= dec_speed

        t_progress = max(0.0, min(1.0, t_progress))

        # Exponential Mapping
        exp_factor = (math.exp(k_val * t_progress) - 1) / (math.exp(k_val) - 1)
        current_tps = 1.889 + (5.0 - 1.889) * exp_factor

        # 3. RUN INFERENCE AND SEND
        results = run_simulation_step(current_tps, current_gear, is_braking=brake_input)

        # Then send the data to Java
        send_to_java(results[0], results[3], honk_active, current_gear)
        # 4. PRINT (Single line update)
        print(
            f"Acc: {btn_pressed} | Brk: {int(brake_input)} | Gear: {current_gear} | TPS: {current_tps:.2f} | RPM: {results[0]:.2f}",
            end='\r')

        # 5. CONSTANT 50Hz TIMING
        elapsed = time.time() - start_time
        sleep_time = max(0.001, 0.02 - elapsed)
        time.sleep(sleep_time)

except KeyboardInterrupt:
    if ser: ser.close()
    print("\nSimulation stopped.")