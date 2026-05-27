import subprocess
import re
import csv
import statistics
import matplotlib.pyplot as plt
import os

# Configurações do experimento
EXECUTABLE = "./cracker.exe"  # Ajustado para o executável do Windows
ALGORITHMS = ["brute", "divide", "dynamic", "genetic"]
ROUNDS = 13
CSV_FILENAME = "resultados_experimento.csv"

def run_experiment():
    # Estrutura para armazenar os resultados
    data = {algo: {'times': [], 'hits': []} for algo in ALGORITHMS}
    all_rows = []

    print(f"Iniciando bateria de testes ({ROUNDS} rodadas por algoritmo)...")

    for algo in ALGORITHMS:
        print(f"--- Testando: {algo.upper()} ---")
        for i in range(ROUNDS):
            print(f"  Rodada {i+1}/{ROUNDS}...", end="", flush=True)
            
           
            command = [EXECUTABLE, "--algo", f"{algo}-mode", "--file", "tests/my_secret.txt"]
            
            # O errors='ignore' protege o Python contra travamentos por causa de acentos mal formatados do C
            result = subprocess.run(command, capture_output=True, text=True, errors='ignore')
            output = result.stdout

            # Regex turbinado: ignora a palavra "Oráculo" bugada e busca direto os dois pontos e o número
            time_match = re.search(r"Tempo:\s+([\d.]+)", output)
            hits_match = re.search(r"Chamadas ao[^\:]*:\s+(\d+)", output)

            if time_match and hits_match:
                time_taken = float(time_match.group(1))
                hits = int(hits_match.group(1))
                
                data[algo]['times'].append(time_taken)
                data[algo]['hits'].append(hits)
                
                # Salva a linha para o CSV
                all_rows.append([algo, i+1, time_taken, hits])
                print(f" OK ({time_taken:.5f}s)")
            else:
                print(" ERRO na leitura da saída!")
                print("Saída do programa:", output)

    return data, all_rows

def save_to_csv(rows):
    print(f"\nSalvando dados brutos em {CSV_FILENAME}...")
    with open(CSV_FILENAME, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Algoritmo", "Rodada", "Tempo_Segundos", "Chamadas_Oraculo"])
        writer.writerows(rows)

def generate_graphs(data):
    print("Gerando gráficos comparativos...")
    
    algos = list(data.keys())
    avg_times = [statistics.mean(data[algo]['times']) for algo in algos]
    avg_hits = [statistics.mean(data[algo]['hits']) for algo in algos]

    # Gráfico 1: Tempo Médio de Execução
    plt.figure(figsize=(10, 5))
    plt.bar(algos, avg_times, color=['red', 'blue', 'green', 'purple'])
    plt.title('Tempo Médio de Execução por Algoritmo (Menor é Melhor)')
    plt.ylabel('Tempo (Segundos)')
    plt.xlabel('Paradigma')
    # Escala logarítmica ativada para evidenciar a disparidade
    plt.yscale('log') 
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.savefig('grafico_tempo.png')
    print(" -> grafico_tempo.png salvo.")

    # Gráfico 2: Média de Chamadas ao Oráculo (Hits)
    plt.figure(figsize=(10, 5))
    plt.bar(algos, avg_hits, color=['red', 'blue', 'green', 'purple'])
    plt.title('Média de Chamadas ao Oráculo por Algoritmo (Menor é Melhor)')
    plt.ylabel('Quantidade de Hits')
    plt.xlabel('Paradigma')
    plt.yscale('log')
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.savefig('grafico_hits.png')
    print(" -> grafico_hits.png salvo.")

if __name__ == "__main__":
    if not os.path.exists(EXECUTABLE):
        print(f"Erro: O executável '{EXECUTABLE}' não foi encontrado na pasta.")
    else:
        results_data, csv_rows = run_experiment()
        save_to_csv(csv_rows)
        generate_graphs(results_data)
        print("\nExperimento concluído com sucesso! Verifique os arquivos gerados na pasta.")