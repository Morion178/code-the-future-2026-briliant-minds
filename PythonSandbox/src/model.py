import torch
import torch.nn as nn


class EngineTwinModel(nn.Module):
    def __init__(self, input_dim=11, hidden_dim=128, output_dim=4):
        super(EngineTwinModel, self).__init__()

        # 1. The GRU layer handles the temporal sequence (the window of 5 steps)
        # batch_first=True means we use the format: [Batch, Time_Steps, Features]
        self.gru = nn.GRU(input_dim, hidden_dim, num_layers=2, batch_first=True, dropout=0.2)

        # 2. Fully connected layers to refine the output
        self.network = nn.Sequential(
            nn.Linear(hidden_dim, 64),
            nn.ReLU(),
            nn.Linear(64, output_dim)
        )

    def forward(self, x):
        # x shape: [Batch, 5, 11]

        # gru_out shape: [Batch, 5, 128]
        # _ is the hidden state (we don't need it for simple prediction)
        gru_out, _ = self.gru(x)

        # We only care about the very LAST step of the sequence (the most recent state)
        # last_time_step shape: [Batch, 128]
        last_time_step = gru_out[:, -1, :]

        # Pass the last state through the final network
        return self.network(last_time_step)