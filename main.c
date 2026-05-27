#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "oracle.h" 

// Protótipos das funções dos algoritmos
void solve_brute_force(void);
void solve_divide_and_conquer(void);
void solve_dynamic_programming(void);
void solve_genetic_algorithm(void);

int main(int argc, char *argv[]) {
    // Verifica a quantidade mínima de argumentos baseada no protocolo da CLI
    if (argc < 4) {
        fprintf(stderr, "Uso recomendado:\n");
        fprintf(stderr, "  %s --algo brute-mode random\n", argv[0]);
        fprintf(stderr, "  %s --algo genetic-mode file-path [caminho_do_arquivo]\n", argv[0]);
        return 1;
    }

    char *algo = argv[2];
    char *mode_str = argv[3];
    char *file_path = NULL;
    int mode = MODE_RANDOM;

    // Trata a leitura a partir de arquivo se especificado
    if (strcmp(mode_str, "file-path") == 0 || strcmp(mode_str, "file") == 0 || strcmp(mode_str, "--file") == 0) {
        if (argc < 5) {
            fprintf(stderr, "Erro: Modo de arquivo selecionado, mas o caminho não foi informado.\n");
            return 1;
        }
        mode = MODE_FILE;
        file_path = argv[4];
    }

    // Inicializa o oráculo (carrega ou gera a senha oculta)
    oracle_init(mode, file_path);

    // Estruturas para medição de tempo de alta precisão
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Orquestra a chamada com base no algoritmo escolhido por argumento
    if (strstr(algo, "brute") != NULL) {
        solve_brute_force();
    } else if (strstr(algo, "divide") != NULL || strstr(algo, "conquer") != NULL) {
        solve_divide_and_conquer();
    } else if (strstr(algo, "genetic") != NULL) {
        solve_genetic_algorithm();
    } else if (strstr(algo, "dynamic") != NULL) { // Correção: Remoção do "mode"
        solve_dynamic_programming();
    } else {
        fprintf(stderr, "Erro: Algoritmo '%s' não reconhecido.\n", algo);
        return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcula o tempo total decorrido em segundos
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Exibe os resultados formatados conforme o protocolo de testes do professor
    printf("\nResultados: \n");
    printf("Tempo: %.5f s\n", elapsed);
    printf("Chamadas ao Oraculo: %lld\n", get_oracle_hits());

    return 0;
}