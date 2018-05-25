//
//  SinglePopulationAlgorithm.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "SinglePopulationAlgorithm.h"
#include "Algorithm.h"
#include "FitnessFunction.h"
#include "Genetics.h"
#include "Breeder.h"
#include "BreedingSelector.h"
#include "Mutator.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

extern GeneticAlgorithm algorithms[];
extern GeneticAlgorithm algorithm;
extern int numAlgorithms;

extern FitnessFunction fitness;
extern Breeder breeder;
extern BreedingSelector selector;
extern Mutator mutator;
extern Interpreter interpreter;

void initSinglePopulation(void){
    algorithms[numAlgorithms].name = "SinglePopulation";
    algorithms[numAlgorithms].run = runSinglePopulation;
    algorithms[numAlgorithms].save = saveSinglePopulation;
    algorithms[numAlgorithms].scan = scanSinglePopulation;
    
    numAlgorithms++;
}

void scanSinglePopulation(FILE *file){
    fscanf(file, "Genome Length: %d\n", &algorithm.genomeLength);
    assert(algorithm.genomeLength <= MAX_DNA_LENGTH);
    fscanf(file, "Population Size: %d\n", &algorithm.populationSize);
    assert(algorithm.populationSize <= MAX_POPULATION_SIZE);
}
void saveSinglePopulation(FILE *file){
    fprintf(file, "Genome Length: %d\n", algorithm.genomeLength);
    fprintf(file, "Population Size: %d\n", algorithm.populationSize);
}

void printPopulationStatus(Population *p);

void runSinglePopulation(FILE *file){
    
    int popSize = algorithm.populationSize;
    
    bool stackAlloc = (2*popSize*sizeof(Genome) < MAX_STACK_USE);
    Genome _genomes[stackAlloc ? popSize : 1];
    Genome _nextGenomes[stackAlloc ? popSize : 1];
    
    Genome *genomes = stackAlloc ? _genomes : malloc(sizeof(Genome)*popSize);
    Genome *nextGenomes = stackAlloc ? _nextGenomes : malloc(sizeof(Genome)*popSize);
    
    Population p;
    p.genomes = genomes;
    initializeRandomPopulation(&p);
    
    
    int best = -1;
    for (int gen = 0; gen < MAX_GENERATION_COUNT; gen++) {
        //printf("Starting gen %d\n", gen);
        for (int i = 0; i < popSize; i++) {
            fitness.calculate(&p.genomes[i]);
        }
        sortPopulation(&p);
        if(selector.copyElite)
            assert(p.bestFitness == -1 || p.bestFitness <= p.sorted[0]->fitness);
        
         p.bestFitness = p.sorted[0]->fitness;
        
        if(p.sorted[0]->fitness > best){
            printf("New Best!\n");
            printPopulationStatus(&p);
            best = p.sorted[0]->fitness;
            if(best == fitness.perfectFitness) break;
        }
        
        if(gen % 1000 == 0){
            printf("\n");
            printf("Generation %d Check in:\n", gen);
            printPopulationStatus(&p);
        }
        
        selector.prep(&p);
        for (int i = 0; i < popSize; i++) {
            Parents par = selector.select(&p, i);
            if(par.p2 != NULL){
                breeder.breed(par.p1, par.p2, &nextGenomes[i]);
                mutator.mutate(&nextGenomes[i]);
                nextGenomes[i].fitness = -1;
            }
            else{
                nextGenomes[i] = *par.p1;
            }
            processGenome(&nextGenomes[i]);
        }
        
        memmove(genomes, nextGenomes, sizeof(Genome)*popSize);
        p.generation++;
        
    }
}

void printPopulationStatus(Population *p){
    printf("Generation %d, Best Fitness: %d/%d\n", p->generation, p->bestFitness, fitness.perfectFitness);
    printf("Code:\n");
    if(strcmp(interpreter.name, "Oyster") == 0){
        for (int i = 0; i < interpreter.numLines; i++) {
            printf("%c: ", 'A' + i);
            for (int j = 0; j < interpreter.lineLength; j++) {
                printf("%c", p->sorted[0]->dna[i*interpreter.lineLength + j]);
            }
            printf("\n");
        }
    }
    else{
        printf("%s\n", p->sorted[0]->dna);
    }
    
    printf("Output: %s\n", p->sorted[0]->program.generic.output);
//Code: %s\nOutput: %s\n", p->generation, p->sorted[0]->fitness, fitness.perfectFitness, p->sorted[0]->dna, p->sorted[0]->program.generic.output);
    printf("{");
    for (int i = 0; i < 15; i++) {
        printf("%d, ", (unsigned char)p->sorted[0]->program.generic.output[i]);
    }
    printf("}\n");
}


