#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "oracle.h"

#define POP_SIZE 100
#define MAX_GENERATIONS 50000


typedef struct {
    char dna[9];
    int fitness;
} Individual;

static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

char get_random_char() {
    return charset[rand() % 62];
}

void init_population(Individual pop[]) {
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 0; j < 8; j++) {
            pop[i].dna[j] = get_random_char();
        }
        pop[i].dna[8] = '\0';
        pop[i].fitness = get_fitness(pop[i].dna);
    }
}


int compare_fitness(const void *a, const void *b) {
    Individual *indA = (Individual *)a;
    Individual *indB = (Individual *)b;
    return indB->fitness - indA->fitness;
}

void solve_genetic_algorithm(void) {
    Individual population[POP_SIZE];
    Individual new_population[POP_SIZE];
    
  
    init_population(population);
    
    int generation = 0;
    
    while (generation < MAX_GENERATIONS) {
        // Ordena a população para colocar os "mais aptos" no topo
        qsort(population, POP_SIZE, sizeof(Individual), compare_fitness);
        
        // Verifica se o melhor indivíduo encontrou a senha (Fitness 8) 
        if (population[0].fitness == 8) {
            printf("Senha descoberta: %s\n", population[0].dna);
            return;
        }
        
        // 3. Seleção e Cruzamento (Elitismo) 
      
        for (int i = 0; i < 10; i++) {
            new_population[i] = population[i];
        }
        
        // Crossover e Mutação para o resto da população 
        for (int i = 10; i < POP_SIZE; i++) {
            // Seleciona pais aleatoriamente entre os 50 melhores
            int parent1_idx = rand() % 50;
            int parent2_idx = rand() % 50;
            
            // Ponto de corte para o crossover (1 a 7)
            int crossover_point = 1 + rand() % 7;
            
            for (int j = 0; j < 8; j++) {
                // Cruzamento
                if (j < crossover_point) {
                    new_population[i].dna[j] = population[parent1_idx].dna[j];
                } else {
                    new_population[i].dna[j] = population[parent2_idx].dna[j];
                }
                
                // Mutação: 10% de chance de um gene sofrer mutação
                if (rand() % 100 < 10) {
                    new_population[i].dna[j] = get_random_char();
                }
            }
            new_population[i].dna[8] = '\0';
            // Avalia o novo indivíduo usando o oráculo
            new_population[i].fitness = get_fitness(new_population[i].dna);
        }
        
        // Atualiza a geração
        for (int i = 0; i < POP_SIZE; i++) {
            population[i] = new_population[i];
        }
        
        generation++;
    }
    
    printf("Falha: A senha nao evoluiu o suficiente após %d geracoes.\n", MAX_GENERATIONS);
}