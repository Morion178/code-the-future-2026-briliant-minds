import pandas as pd

# Load the messy data
df = pd.read_csv("../data/EngineFaultDB_Final.csv")

# Count before for your report
total_rows = len(df)
faulty_rows = len(df[df['Fault'] != 0])

# Filter: Keep ONLY rows where Fault is exactly 0
df_healthy = df[df['Fault'] == 0].copy()

# Save as a new file so you don't lose the original
df_healthy.to_csv("../data/Engine_Healthy_Only.csv", index=False)

print(f"Cleanup Complete!")
print(f"Removed {faulty_rows} faulty rows.")
print(f"Total Healthy Rows remaining: {len(df_healthy)}")