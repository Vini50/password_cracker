#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"

// Função auxiliar para resolver um subproblema (encontrar 4 caracteres)
bool find_half_password(char *half_result, int start_pos) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int base = 62;
    
    char attempt[5];
    attempt[4] = '\0'; // Terminador da string para o pedaço de 4 chars
    
    // Array para controlar os índices (nosso "hodômetro" menor)
    int indices[4] = {0, 0, 0, 0};
    
    while (true) {
        // Constrói a string candidata para este subproblema
        for (int i = 0; i < 4; i++) {
            attempt[i] = charset[indices[i]];
        }
        
        // Verifica apenas o pedaço na posição especificada usando o oráculo
        if (check_partial(attempt, start_pos)) {
            strcpy(half_result, attempt);
            return true; // Pedaço encontrado!
        }
        
        // Lógica de incremento para 4 posições
        int pos = 3; 
        while (pos >= 0) {
            indices[pos]++;
            if (indices[pos] < base) {
                break; 
            }
            indices[pos] = 0; 
            pos--;
        }
        
        // Invariante de laço: Se o 'pos' cair abaixo de 0, significa que o array 'indices' 
        // completou todo o ciclo (de 0,0,0,0 até 61,61,61,61) e todas as permutações 
        // do subespaço foram verificadas.
        if (pos < 0) {
            break; 
        }
    }
    return false;
}

void solve_divide_and_conquer(void) {
    char first_half[5];
    char second_half[5];
    char full_password[9];

    // Conquista a primeira metade (índices de 0 a 3 da senha original)
    if (find_half_password(first_half, 0)) {
        
        // Conquista a segunda metade (índices de 4 a 7 da senha original)
        if (find_half_password(second_half, 4)) {
            
            //  Combina as soluções parciais para formar a solução final
            sprintf(full_password, "%s%s", first_half, second_half);
            
            // imprimir a senha apenas no final 
            printf("Senha descoberta: %s\n", full_password);
            return;
        }
    }
    
    printf("Falha: Nao foi possivel encontrar a senha com Divisao e Conquista.\n");
}
