import pandas as pd
import matplotlib.pyplot as plt

# Load the results from the CSV file
df = pd.read_csv('results.csv')  # Make sure the path is correct

# Execution time per algorithm for each dataset
plt.figure(figsize=(10, 6))
for dataset in df['Dataset'].unique():
    subset = df[df['Dataset'] == dataset]
    plt.plot(subset['Algorithm'], subset['Execution Time (ms)'], marker='o', label=dataset)

plt.title('Execution Time by Algorithm')
plt.xlabel('Algorithm')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.savefig('execution_time_comparison.png')
plt.close()

# Total profit per algorithm for each dataset
plt.figure(figsize=(10, 6))
for dataset in df['Dataset'].unique():
    subset = df[df['Dataset'] == dataset]
    plt.plot(subset['Algorithm'], subset['Total Profit'], marker='o', label=dataset)

plt.title('Total Profit by Algorithm')
plt.xlabel('Algorithm')
plt.ylabel('Total Profit')
plt.legend()
plt.grid(True)
plt.savefig('total_profit_comparison.png')
plt.close()

print("Graphs generated in png format in results_and_graphs.")
