# 🔐 Password Cracker: Estudo de Paradigmas Algorítmicos

Este projeto é uma simulação de *Pentesting* (testes de intrusão) focada na quebra de uma senha de 8 caracteres alfanuméricos. O objetivo central é demonstrar, na prática, as diferenças de desempenho e complexidade entre quatro paradigmas clássicos de projeto de algoritmos ao interagir com um sistema de validação (Oráculo).

O espaço de busca total do problema é de 62^8 (aproximadamente 218.3 trilhões de combinações).

## 🧠 Paradigmas Implementados

1. **Força Bruta (Exaustiva):** Atua como nossa linha de base (*baseline*), testando todas as combinações sequencialmente a partir da senha em my_secret.txt.
2. **Divisão e Conquista:** Reduz a complexidade massivamente quebrando a senha de 8 dígitos em dois subproblemas independentes de 4 dígitos.
3. **Programação Dinâmica (Memoização):** Utiliza um dicionário de prefixos comuns (ex: "admin", "1234") e poda (*backtracking*) para evitar reprocessamento e ignorar ramos de busca inválidos.
4. **Algoritmos Genéticos (Heurística):** Evolui uma população de strings aleatórias através de seleção, cruzamento e mutação, guiada por uma função de *Fitness* que avalia a quantidade de caracteres corretos na posição exata.

## 📂 Estrutura do Projeto

```text
password_cracker/
├── src/
│   ├── oracle.c / oracle.h     # Lógica do Oráculo e encapsulamento da senha secreta
│   ├── brute_force.c           # Implementação da Força Bruta
│   ├── divide_conquer.c        # Implementação da Divisão e Conquista
│   ├── dynamic.c               # Implementação da Programação Dinâmica
│   └── genetic.c               # Implementação do Algoritmo Genético
├── tests/
│   └── my_secret.txt           # Arquivo contendo a senha alvo para os testes (ex: adminaaa)
├── analysis.py                 # Script orquestrador em Python para gerar métricas e gráficos
├── Makefile                    # Automação da compilação em C
└── main.c                      # Ponto de entrada (CLI)
## 🚀 Como Compilar e Executar

### Pré-requisitos
* Compilador GCC (`gcc`) e `make` (ou `mingw32-make` no Windows).
* Python 3 com `matplotlib` instalado (para geração de gráficos).

### 1. Compilação
No terminal, na raiz do projeto, execute:

gcc -Wall -Wextra -O3 -Isrc main.c src/oracle.c src/brute_force.c src/divide_conquer.c src/dynamic.c src/genetic.c -o cracker.exe

### 2. Testes Manuais (CLI)
O programa suporta argumentos de linha de comando para testar diferentes modos e algoritmos.

**Modo Aleatório (Senha gerada na hora):**

./cracker.exe --algo brute-mode random


**Modo Arquivo (Avaliação baseada em um arquivo de texto):**

./cracker.exe --algo genetic-mode file-path tests/my_secret.txt

*Substitua "genetic-mode" por: brute-mode, divide-mode ou dynamic-mode.*

### 3. Automação e Geração de Gráficos
Para executar uma bateria de testes de estresse (13 rodadas) e extrair comparações reais de **Tempo de CPU** vs **Chamadas ao Oráculo**, rode o script em Python:

python analysis.py

*(Isso irá gerar os arquivos `resultados_experimento.csv`, `grafico_tempo.png` e `grafico_hits.png` na raiz do projeto).*

---
*Projeto desenvolvido para fins acadêmicos - Estudo de Complexidade de Algoritmos.*
