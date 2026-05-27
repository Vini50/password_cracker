#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"

// Variáveis globais para o algoritmo
static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const int base = 62;

// A função principal que o main.c vai chamar
void solve_brute_force(void) {
    char attempt[9];
    attempt[8] = '\0';
    
    // Vetor para rastrear os índices de cada caractere na string
    int indices[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Constrói a string inicial (AAAAAAAA)
    for (int i = 0; i < 8; i++) {
        attempt[i] = charset[indices[i]];
    }

    bool password_found = false;

    while (!password_found) {
        // Verifica no oráculo usando a função exigida para Força Bruta
        if (check_full(attempt)) {
            password_found = true; 
            break; 
        }
        
        // Lógica de incremento sequencial otimizada (atualiza só a letra que mudou)
        int pos = 7;
        while (pos >= 0) { 
            indices[pos]++;
            if (indices[pos] < base) {
                attempt[pos] = charset[indices[pos]];
                break; // Incrementou sem "vai um", podemos testar a nova senha
            }
            
            // "Vai um": zera a posição atual e move para a esquerda
            indices[pos] = 0; 
            attempt[pos] = charset[0];
            pos--;
        }
        
        // Se a posição ficou menor que 0, esgotamos todas as combinações
        if (pos < 0) {
            break;
        }
    }

    // O log deve registrar a senha descoberta apenas no final
    if (password_found) {
        printf("Senha descoberta: %s\n", attempt);
    } else {
        printf("Falha: Todas as combinacoes foram testadas.\n");
    }
}