#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"

// Tabela de memoização/dicionário de prefixos comuns sugerida no documento
const char* common_prefixes[] = {"admin", "1234", "pass", "root", "user", "test"};
const int num_prefixes = 6;

static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Função recursiva que constrói a senha e poda ramos inválidos
bool solve_recursive(char* current_attempt, int pos) {
    // Caso base: chegamos a 8 caracteres
    if (pos == 8) {
        current_attempt[8] = '\0';
        // Apenas para contabilizar o hit final e confirmar a string completa
        if (check_full(current_attempt)) {
            printf("Senha descoberta: %s\n", current_attempt);
            return true;
        }
        return false;
    }

    // Estratégia de Memoização (Tabela)
    if (pos == 0) {
        for (int i = 0; i < num_prefixes; i++) {
            int len = strlen(common_prefixes[i]);
            if (len <= 8) {
                // Se o prefixo comum for válido para o início da senha...
                if (check_partial(common_prefixes[i], pos)) {
                    strcpy(current_attempt, common_prefixes[i]);
                    // ...avançamos direto na árvore, pulando milhares de testes char por char!
                    if (solve_recursive(current_attempt, pos + len)) {
                        return true;
                    }
                }
            }
        }
    }

    // Construção incremental (Bottom-Up)
    for (int i = 0; i < 62; i++) {
        current_attempt[pos] = charset[i];
        
        char temp_str[2] = {charset[i], '\0'};
        
        //  O oráculo avalia apenas a posição atual.
        // Se retornar falso, todo esse ramo é descartado, quebrando o laço de repetição inútil.
        if (check_partial(temp_str, pos)) {
            // Se o caractere é válido nesta posição, aprofundamos na recursão
            if (solve_recursive(current_attempt, pos + 1)) {
                return true;
            }
        }
    }

    return false; // Retorna falso se nenhuma combinação neste ramo for válida (backtracking)
}

void solve_dynamic_programming(void) {
    char attempt[9] = {0}; // Array preenchido com zeros
    
    if (!solve_recursive(attempt, 0)) {
        printf("Falha: Nao foi possivel encontrar a senha com Programacao Dinamica.\n");
    }
}
