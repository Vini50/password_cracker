#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"


static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const int base = 62;


void solve_brute_force(void) {
    char attempt[9];
    attempt[8] = '\0';
    
  
    int indices[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    
    for (int i = 0; i < 8; i++) {
        attempt[i] = charset[indices[i]];
    }

    bool password_found = false;

    while (!password_found) {
       
        if (check_full(attempt)) {
            password_found = true; 
            break; 
        }
        
        
        int pos = 7;
        while (pos >= 0) { 
            indices[pos]++;
            if (indices[pos] < base) {
                attempt[pos] = charset[indices[pos]];
                break; 
            }
            
            
            indices[pos] = 0; 
            attempt[pos] = charset[0];
            pos--;
        }
        
        
        if (pos < 0) {
            break;
        }
    }

    
    if (password_found) {
        printf("Senha descoberta: %s\n", attempt);
    } else {
        printf("Falha: Todas as combinacoes foram testadas.\n");
    }
}
