import pandas as pd
import numpy as np


def generate_accurate_master():
    # 1. Load your cleaned healthy data
    # Ensure this file was created using only Fault == 0 rows
    df_healthy = pd.read_csv("../data/Engine_Healthy_Only.csv")

    # Identify the last known good state to prevent the "Big Jump"
    last_row = df_healthy.iloc[-1]
    last_tps = last_row['TPS']
    last_rpm = last_row['RPM']
    last_speed = last_row['Speed']

    # 2. Setup the Ramp to 9000 RPM
    samples = 10000
    # Ramp TPS from current last value to 5.0V
    tps_synth = np.linspace(last_tps, 5.0, samples)

    # Quadratic RPM ramp starting exactly at last_rpm
    tps_range = 5.0 - last_tps
    rpm_range = 9000 - last_rpm
    rpm_synth = last_rpm + (rpm_range / (tps_range ** 2)) * (tps_synth - last_tps) ** 2

    # 3. Build DataFrame following your specific 15-column header
    df_synth = pd.DataFrame({
        'Fault': 0,
        'MAP': np.linspace(last_row['MAP'], 100.0, samples),
        'TPS': tps_synth,
        'Force': rpm_synth * 0.12,
        'Power': rpm_synth * 0.06,
        'RPM': rpm_synth,
        'Consumption L/H': (rpm_synth * 0.002) + (tps_synth * 0.5),
        'Consumption L/100KM': (rpm_synth * 0.0025) + (tps_synth * 1.5),
        'Speed': np.linspace(last_speed, rpm_synth.max() * 0.028, samples),
        'CO': np.linspace(last_row['CO'], 0.01, samples),
        'HC': np.linspace(last_row['HC'], 20.0, samples),
        'CO2': ((rpm_synth * 0.0025) + (tps_synth * 1.5)) * 2.31,
        'O2': 0.4,
        'Lambda': 1.0,
        'AFR': 14.7
    })

    # 4. Merge and Smooth the Junction
    # We combine them, ensuring columns match exactly
    df_master = pd.concat([df_healthy, df_synth], ignore_index=True)

    # Smooth the junction point specifically for RPM and TPS to avoid AI glitches
    df_master['RPM'] = df_master['RPM'].rolling(window=10, min_periods=1).mean()
    df_master['TPS'] = df_master['TPS'].rolling(window=5, min_periods=1).mean()

    # 5. Save
    output_path = "../data/Engine_Master_9000.csv"
    df_master.to_csv(output_path, index=False)

    print("-" * 40)
    print(f"Master Dataset Synchronized: {output_path}")
    print(f"Stitch Point: TPS {last_tps:.2f}V -> RPM {last_rpm:.1f}")
    print(f"Final Redline: {df_master['RPM'].max():.1f} RPM")
    print("-" * 40)


if __name__ == "__main__":
    generate_accurate_master()