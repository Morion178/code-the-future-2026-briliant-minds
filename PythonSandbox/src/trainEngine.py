import pandas as pd
import numpy as np
import torch
import torch.nn as nn
import joblib
from sklearn.preprocessing import RobustScaler, MinMaxScaler
from model import EngineTwinModel

# 1. Load Original Master (NO OVERSAMPLING)
df = pd.read_csv("../data/Engine_Master_9000.csv")

features = ['TPS', 'MAP', 'Force', 'Power', 'RPM', 'Speed', 'Consumption L/H', 'Consumption L/100KM', 'CO', 'HC', 'CO2', 'O2', 'Lambda', 'AFR']
targets = ['RPM', 'Speed', 'CO2', 'Consumption L/100KM']

# 2. Scaling (MinMaxScaler helps define the "Floor")
scaler_X = RobustScaler()
scaler_y = MinMaxScaler()

X_scaled = scaler_X.fit_transform(df[features].values)
y_scaled = scaler_y.fit_transform(df[targets].values)

# 3. Create Sequences
def create_sequences(X, y, window_size=5):
    X_seq, y_seq = [], []
    for i in range(len(X) - window_size):
        X_seq.append(X[i: i + window_size])
        y_seq.append(y[i + window_size])
    return np.array(X_seq), np.array(y_seq)

X_seq, y_seq = create_sequences(X_scaled, y_scaled, window_size=5)
X_tensor = torch.FloatTensor(X_seq)
y_tensor = torch.FloatTensor(y_seq)

# 4. Create Loss Weights
# We calculate a weight for every row. If RPM is low, weight is high.
# y_seq[:, 0] is the normalized RPM target
rpm_targets = y_seq[:, 0]
# Weight formula: higher weight for values closer to 0 (Idle)
weights = torch.FloatTensor(1.0 + 3.0 * (1.0 - rpm_targets)).unsqueeze(1)

# 5. Model Setup
model = EngineTwinModel(input_dim=len(features), hidden_dim=256, output_dim=len(targets))
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# Custom Weighted MSE Loss
def weighted_mse_loss(input, target, weight):
    return (weight * (input - target) ** 2).mean()

# 6. Training Loop
epochs = 20 # Reduced epochs to prevent overfitting
print(f"Training with Smart Weighting on {len(df)} rows...")

for epoch in range(epochs):
    model.train()
    optimizer.zero_grad()

    preds = model(X_tensor)
    loss = weighted_mse_loss(preds, y_tensor, weights)

    loss.backward()
    torch.nn.utils.clip_grad_norm_(model.parameters(), max_norm=0.5)
    optimizer.step()

    if (epoch + 1) % 5 == 0:
        print(f"Epoch {epoch + 1:2d} | Weighted Loss: {loss.item():.6f}")

# 7. Save
torch.save(model.state_dict(), "../models/engine_twin.pth")
joblib.dump(scaler_X, "../models/scaler_X.pkl")
joblib.dump(scaler_y, "../models/scaler_y.pkl")
print("--- Training Complete: Physics Preserved ---")