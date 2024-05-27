import pandas as pd

# Columns in the CSV files
col_list = ["sent.seconds", "sent.microseconds", "received.seconds", 
            "received.microseconds", "sampleTimeStamp.seconds", 
            "sampleTimeStamp.microseconds", "groundSteering"]

# Read the CSV files as pandas dataframes
rec1 = pd.read_csv('rec3.csv', usecols=col_list, sep=';')
rec2 = pd.read_csv('lightning.csv', usecols=col_list, sep=';')

accepted = 0

# Iterate over rows of both dataframes using zip
for s1, s2 in zip(rec1.iterrows(), rec2.iterrows()):
    GSR1 = s1[1]['groundSteering']
    GSR2 = s2[1]['groundSteering']

    # Set bounds based on GSR1
    if GSR1 == 0:
        upper = 0.05
        lower = -0.05
    elif GSR1 > 0:
        upper = GSR1 * 1.5
        lower = GSR1 * 0.5
    else:
        upper = GSR1 * 0.5
        lower = GSR1 * 1.5

    # Check if GSR2 is within bounds
    if lower <= GSR2 <= upper:
        accepted += 1

# Calculate and print the percentage of accepted frames
total_frames = len(rec1)
percentage = (accepted / total_frames) * 100
print(f'Percentage: {percentage:.2f}%')
print(f'Accepted frames: {accepted}')
