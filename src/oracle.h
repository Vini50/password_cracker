#ifndef ORACLE_H
#define ORACLE_H

#include <stdbool.h>

// Modos de operação
#define MODE_RANDOM 0
#define MODE_FILE 1

// Inicializa o oráculo: gera senha aleatória ou lê de um arquivo
void oracle_init(int mode, const char* path);

// Força Bruta: Compara a string inteira (8 chars)
bool check_full(const char* attempt);

// Divisão e Conquista / Programação Dinâmica:
// Compara uma parte da senha em uma posição específica
bool check_partial(const char* part, int start_pos);

// Algoritmos Genéticos: Retorna quantos caracteres estão na posição correta (0-8)
int get_fitness(const char* attempt);

// Retorna o número de chamadas (hits) feitas ao oráculo
long long get_oracle_hits();

#endif
