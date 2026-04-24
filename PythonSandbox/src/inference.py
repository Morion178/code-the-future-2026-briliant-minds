import torch
import joblib
import numpy as np
import serial
import time
import math
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


def run_simulation_step(new_tps, is_braking=False):
    global history_buffer
    current_row = history_buffer[-1].copy()

    if is_braking:
        active_tps = 1.889
        current_row[7] = current_row[7] * 0.85
    else:
        active_tps = new_tps

    current_row[1] = active_tps
    history_buffer.append(current_row)
    if len(history_buffer) > 5:
        history_buffer.pop(0)

    history_array = np.array(history_buffer)
    history_scaled = scaler_X.transform(history_array)
    input_tensor = torch.FloatTensor(history_scaled).unsqueeze(0)

    with torch.no_grad():
        prediction_scaled = model(input_tensor)

    prediction_real = scaler_y.inverse_transform(prediction_scaled.numpy())[0]
    ai_rpm = prediction_real[0]

    # Dynamic Range Correction
    if active_tps <= 2.0:
        res_rpm = (ai_rpm * 0.2) + (1192.0 * 0.8)
        if is_braking: res_rpm *= 0.9
    elif 3.0 < active_tps < 4.8:
        weight = (active_tps - 3.0) / (4.8 - 3.0)
        target_mid = 7500.0
        res_rpm = (ai_rpm * (1 - weight)) + (target_mid * weight)
    elif active_tps >= 4.8:
        res_rpm = (ai_rpm * 0.2) + (9000.0 * 0.8)
    else:
        res_rpm = ai_rpm

    final_speed = current_row[7] if is_braking else prediction_real[1]
    history_buffer[-1][4], history_buffer[-1][7] = res_rpm, final_speed
    history_buffer[-1][10], history_buffer[-1][6] = prediction_real[2], prediction_real[3]

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

        # 3. RUN INFERENCE
        results = run_simulation_step(current_tps, is_braking=brake_input)

        # 4. PRINT (Single line update)
        print(
            f"Acc: {btn_pressed} | Brk: {int(brake_input)} | Gear: {current_gear} | TPS: {current_tps:.2f} | RPM: {results[0]:.2f}",
            end='\r')

        # 5. CONSTANT 50Hz TIMING
        time.sleep(0.02)

except KeyboardInterrupt:
    if ser: ser.close()
    print("\nSimulation stopped.")