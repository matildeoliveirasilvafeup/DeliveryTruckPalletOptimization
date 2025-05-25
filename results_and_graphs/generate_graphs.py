import pandas as pd
import matplotlib.pyplot as plt
import re
import os

script_dir = os.path.dirname(__file__)
csv_path = os.path.join(script_dir, "results.csv")


# Lê o ficheiro results.csv
df = pd.read_csv(csv_path)

# Limpar espaços em branco no nome do dataset
df['Dataset'] = df['Dataset'].str.strip()

# Extrair N do nome do dataset
def extract_N(dataset_name):
    match = re.search(r'Pallets_(\d+)', dataset_name)
    return int(match.group(1)) if match else None

df['N'] = df['Dataset'].apply(extract_N)

print(df[['Dataset', 'N']].drop_duplicates())
print("Valores únicos de N:", df['N'].unique())

# Filtrar apenas Ns desejados
Ns_to_plot = [1, 10, 100, 1000]
df = df[df['N'].isin(Ns_to_plot)]
df = df.sort_values(by='N')

# Normalizar nomes dos algoritmos para evitar duplicados
df['Algorithm'] = df['Algorithm'].str.strip().str.lower()

print("Algoritmos únicos normalizados:", df['Algorithm'].unique())

# Plot Execution Time
plt.figure(figsize=(10, 6))
for algorithm in df['Algorithm'].unique():
    subset = df[df['Algorithm'] == algorithm]
    plt.plot(subset['N'], subset['Execution Time (ms)'], marker='o', label=algorithm)
plt.title('Execution Time by Algorithm vs N')
plt.xlabel('N (Instance Size)')
plt.ylabel('Execution Time (ms)')
plt.xscale('log')
plt.xticks(Ns_to_plot, Ns_to_plot)
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.savefig('execution_time_comparison.png')  # Guarda aqui na pasta results_and_graphs
plt.close()

# Plot Total Profit
plt.figure(figsize=(10, 6))
for algorithm in df['Algorithm'].unique():
    subset = df[df['Algorithm'] == algorithm]
    plt.plot(subset['N'], subset['Total Profit'], marker='o', label=algorithm)
plt.title('Total Profit by Algorithm vs N')
plt.xlabel('N (Instance Size)')
plt.ylabel('Total Profit')
plt.xscale('log')
plt.xticks(Ns_to_plot, Ns_to_plot)
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.savefig('total_profit_comparison.png')  # Também aqui
plt.close()

print("Gráficos gerados em: ./ (pasta results_and_graphs)")
print(df.head(10))
print(df['Dataset'].unique())
