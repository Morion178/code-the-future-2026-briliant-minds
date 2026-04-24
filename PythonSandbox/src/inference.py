import torch
import joblib
import numpy as np
from model import EngineTwinModel

# 1. Initialize Model (14 features: Fault is excluded from training input)
model = EngineTwinModel(input_dim=14, hidden_dim=256, output_dim=4)
model.load_state_dict(torch.load("../models/engine_twin.pth", weights_only=True))
model.eval()

scaler_X = joblib.load("../models/scaler_X.pkl")
scaler_y = joblib.load("../models/scaler_y.pkl")

# 2. REAL INITIAL STATE (from your snippet)
# Order: MAP, TPS, Force, Power, RPM, Consumption L/H, Consumption L/100KM, Speed, CO, HC, CO2, O2, Lambda, AFR
initial_state = np.array([
    3.549,  # MAP
    1.889,  # TPS
    7.428,  # Force
    5.227,  # Power
    1500.7,  # RPM
    3.057,  # Cons L/H
    11.72,  # Cons L/100KM
    24.901,  # Speed
    0.46,  # CO
    196.1,  # HC
    14.356,  # CO2
    1.08,  # O2
    1.047,  # Lambda
    15.385  # AFR
])

history_buffer = [initial_state.copy() for _ in range(5)]


def run_simulation_step(new_tps, is_braking=False):
    global history_buffer

    current_row = history_buffer[-1].copy()

    # 1. BRAKE LOGIC OVERRIDE
    if is_braking:
        # If braking, force throttle to idle regardless of input
        active_tps = 1.889
        # Apply a "Friction Decay" to the speed currently in the buffer (index 7)
        # 0.85 means losing 15% speed per step—change to 0.95 for a softer brake
        current_row[7] = current_row[7] * 0.85
    else:
        active_tps = new_tps

    current_row[1] = active_tps  # TPS is index 1

    # Update history
    history_buffer.append(current_row)
    if len(history_buffer) > 5:
        history_buffer.pop(0)

    # 2. INFERENCE
    history_array = np.array(history_buffer)
    history_scaled = scaler_X.transform(history_array)
    input_tensor = torch.FloatTensor(history_scaled).unsqueeze(0)

    with torch.no_grad():
        prediction_scaled = model(input_tensor)

    prediction_real = scaler_y.inverse_transform(prediction_scaled.numpy())[0]
    ai_rpm = prediction_real[0]

    # 3. DYNAMIC RANGE CORRECTION (Using active_tps)
    if active_tps <= 2.0:
        res_rpm = (ai_rpm * 0.2) + (1192.0 * 0.8)
        # If braking, we want the RPM to drop even faster toward idle
        if is_braking:
            res_rpm = res_rpm * 0.9  # Additional 10% RPM drop per step

    elif 3.0 < active_tps < 4.8:
        weight = (active_tps - 3.0) / (4.8 - 3.0)
        target_mid = 7500.0
        res_rpm = (ai_rpm * (1 - weight)) + (target_mid * weight)

    elif active_tps >= 4.8:
        res_rpm = (ai_rpm * 0.2) + (9000.0 * 0.8)
    else:
        res_rpm = ai_rpm

    # 4. FEEDBACK UPDATE
    # When braking, we use our decayed speed instead of the AI's predicted speed
    final_speed = current_row[7] if is_braking else prediction_real[1]

    history_buffer[-1][4] = res_rpm  # RPM
    history_buffer[-1][7] = final_speed  # Speed
    history_buffer[-1][10] = prediction_real[2]  # CO2
    history_buffer[-1][6] = prediction_real[3]  # Fuel

    return [res_rpm, prediction_real[2], prediction_real[3], final_speed]

# --- EXTENDED STABILITY DRIVE CYCLE ---
# We use longer durations to ensure the GRU's hidden state reaches an equilibrium.
dynamic_scenario = [
    (1.9, 20, "INITIAL IDLE"),   # Establish floor
    (5.0, 30, "ACCELERATING"),   # Get up to max speed/RPM
    (1.9, 20, "EMERGENCY BRAKE"), # New brake test stage
    (1.9, 30, "POST-BRAKE IDLE")  # Verify it returns to stable idle
]

print(f"{'Stage':<16} | {'Step':<4} | {'TPS':<4} | {'RPM':<8} | {'CO2':<6} | {'Fuel':<6} | {'Speed':<6}")
print("-" * 75)

for tps_val, duration, label in dynamic_scenario:
    for i in range(duration):
        # Trigger the braking logic only during the "EMERGENCY BRAKE" stage
        braking_active = (label == "EMERGENCY BRAKE")

        # results now returns [RPM, CO2, Fuel, Speed]
        results = run_simulation_step(tps_val, is_braking=braking_active)

        print(
            f"{label:<16} | {i + 1:<4} | {tps_val:<4.1f} | {results[0]:<8.2f} | {results[1]:<6.2f} | {results[2]:<6.2f} | {results[3]:<6.2f}")

print("-" * 75)
print("Brake Test Complete.")