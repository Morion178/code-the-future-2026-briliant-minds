import torch
import joblib
import numpy as np
import serial
import time
import math
import socket
from model import EngineTwinModel

#----------------------------------------------------------
# initialize model
model = EngineTwinModel(input_dim=14, hidden_dim=256, output_dim=4)
model.load_state_dict(torch.load("../models/engine_twin.pth", weights_only=True))
model.eval()

scaler_X = joblib.load("../models/scaler_X.pkl")
scaler_y = joblib.load("../models/scaler_y.pkl")

#-----------------------------------------------------------
# serial and udp setup
SERIAL_PORT = 'COM15'
BAUD_RATE = 115200
UDP_IP = "127.0.0.1"  # "127.0.0.1" if Java is on the same PC
UDP_PORT = 5005       # Pick a port (ensure it's the same in Java)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#-----------------------------------------------------------
# transmission data
GEAR_RATIOS = {
    0: 0.0,
    1: 3.5,
    2: 2.1,
    3: 1.5,
    4: 1.1,
    5: 0.9,
    6: 0.7,
    7: 0.6
}
FINAL_DRIVE = 3.42  # differential
WHEEL_CIRCUMFERENCE = 2.0  # in m


def send_to_java(rpm, speed, honk, gear):

    #temp, co2 and cons aproximation
    sim_temp = 85.0 + (rpm / 2000.0)  # Temp rises slightly with RPM
    sim_co2 = 120 + (rpm / 10.0)  # CO2 rises with RPM
    sim_l100 = 0.0 if speed < 5 else (rpm / 1200.0)  # Fuel consumption logic

    # construct data string for java app
    data_list = [
        round(rpm, 1),
        round(speed, 1),
        round(sim_temp, 1),
        round(sim_co2, 0),
        round(sim_l100, 1),
        int(honk),
        int(gear)
    ]

    #send to java app
    message = ",".join(map(str, data_list))
    sock.sendto(message.encode(), (UDP_IP, UDP_PORT))

#try serial port connect
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    print(f"Connected to ESP32 on {SERIAL_PORT}")
except Exception as e:
    print(f"Serial Error: {e}")
    ser = None


#initial engine state
initial_state = np.array([
    3.549, 1.889, 7.428, 5.227, 1192.769, 3.057, 11.72, 24.901,
    0.46, 196.089, 14.356, 1.08, 1.047, 15.385
])
history_buffer = [initial_state.copy() for _ in range(5)]

#values for input delay
t_progress = 0.0  # The 0.0 to 1.0 incrementer
k_val = 2.5  # Curvature (Higher = more exponential/aggressive)
inc_speed = 0.02  # Speed of rev up (t increases by this much per step)
dec_speed = 0.015  # Speed of rev down (t decreases by this much per step)


def run_simulation_step(new_tps, gear, is_braking=False):
    global history_buffer
    current_row = history_buffer[-1].copy()

    #idle tps is 1.889
    active_tps = 1.889 if is_braking else new_tps
    current_row[1] = active_tps

    #ai input processing
    history_buffer.append(current_row)
    if len(history_buffer) > 5: history_buffer.pop(0)

    history_array = np.array(history_buffer)
    history_scaled = scaler_X.transform(history_array)
    input_tensor = torch.FloatTensor(history_scaled).unsqueeze(0)

    with torch.no_grad():
        prediction_scaled = model(input_tensor)

    prediction_real = scaler_y.inverse_transform(prediction_scaled.numpy())[0]
    ai_rpm = prediction_real[0]

    #tps enhance
    if active_tps <= 2.0:
        res_rpm = (ai_rpm * 0.1) + (1192.0 * 0.9)
    else:
        weight = (active_tps - 2.0) / (4.8 - 2.0)
        target_rpm = 1192.0 + (weight * (9000.0 - 1192.0))
        res_rpm = (ai_rpm * 0.2) + (target_rpm * 0.8)

    #gear calculation
    #formula: Speed (km/h) = (RPM * Wheel_Circ * 60) / (Gear_Ratio * Final_Drive * 1000)
    ratio = GEAR_RATIOS.get(gear, 0.0)

    if ratio > 0 and not is_braking:
        calculated_speed = (res_rpm * WHEEL_CIRCUMFERENCE * 60) / (ratio * FINAL_DRIVE * 1000)
        #bring speed calculation towards input speed
        final_speed = (calculated_speed * 0.7) + (prediction_real[1] * 0.3)
    elif is_braking:
        final_speed = max(0, current_row[7] * 0.85)
    else:
        final_speed = 0  #stop

    # 5. buffer update + low and high cap
    res_rpm = max(800.0, min(9500.0, res_rpm))

    history_buffer[-1][4] = res_rpm
    history_buffer[-1][7] = final_speed

    return [res_rpm, prediction_real[2], prediction_real[3], final_speed]


#debug info - btns presser
print(f"{'Btn':<4} | {'Brk':<4} | {'Gear':<4} | {'T-Prog':<8} | {'Exp-TPS':<7} | {'RPM':<8}")
print("-" * 65)

#btnstate init
btn_pressed = 0
brake_input = False
current_gear = 0
honk_active = False


try:
    while True:
        start_time = time.time()

        #read serial
        if ser and ser.in_waiting > 0:

            if ser.in_waiting > 100: #delete old input buffers that are stored in mem
                ser.reset_input_buffer()
            try:
                #data read and decode only if no error
                raw_data = ser.readline()
                line = raw_data.decode('utf-8', errors='ignore').strip()

                if line and "," in line:
                    parts = line.split(',')
                    if len(parts) >= 4:
                        btn_pressed = int(parts[0])
                        brake_input = bool(int(parts[1]))
                        honk_active = bool(int(parts[2]))
                        current_gear = int(parts[3])
                        print(f"DEBUG RAW: {btn_pressed, brake_input, honk_active, current_gear}")
                        #debug log

            except Exception as e:
                print(f"Decode Error: {e}")
                continue

        #getting value progress through exponential iteration
        if btn_pressed == 1:
            t_progress += inc_speed
        else:
            t_progress -= dec_speed

        t_progress = max(0.0, min(1.0, t_progress))

        # Exponential Mapping
        exp_factor = (math.exp(k_val * t_progress) - 1) / (math.exp(k_val) - 1)
        current_tps = 1.889 + (5.0 - 1.889) * exp_factor

        #send ai data and receive sim step
        results = run_simulation_step(current_tps, current_gear, is_braking=brake_input)

        #send to java app
        send_to_java(results[0], results[3], honk_active, current_gear)
        #debug print
        print(
            f"Acc: {btn_pressed} | Brk: {int(brake_input)} | Gear: {current_gear} | TPS: {current_tps:.2f} | RPM: {results[0]:.2f}",
            end='\r')

        # 5.50hz timing
        elapsed = time.time() - start_time
        sleep_time = max(0.001, 0.02 - elapsed)
        time.sleep(sleep_time)

#add endmsj
except KeyboardInterrupt:
    if ser: ser.close()
    print("\nSimulation stopped, thank you for simulating =D.")