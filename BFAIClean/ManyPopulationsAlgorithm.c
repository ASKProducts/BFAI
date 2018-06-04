//
//  ManyPopulationsAlgorithm.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/14/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "ManyPopulationsAlgorithm.h"
#include "Algorithm.h"
#include "FitnessFunction.h"
#include "Genetics.h"
#include "Breeder.h"
#include "BreedingSelector.h"
#include "Mutator.h"
#include <assert.h>
#include <stdlib.h>
#include "Timer.h"
#include <string.h>

extern GeneticAlgorithm algorithms[];
extern GeneticAlgorithm algorithm;
extern int numAlgorithms;

extern FitnessFunction fitness;
extern Breeder breeder;
extern BreedingSelector selector;
extern Mutator mutator;
extern Interpreter interpreter;

extern bool isRunningPng;

void initManyPopulations(void){
    algorithms[numAlgorithms].name = "ManyPopulations";
    algorithms[numAlgorithms].run = runManyPopulations;
    algorithms[numAlgorithms].save = saveManyPopulations;
    algorithms[numAlgorithms].scan = scanManyPopulations;
    
    numAlgorithms++;
}

void scanManyPopulations(FILE *file){
    fscanf(file, "Genome Length: %d\n", &algorithm.genomeLength);
    assert(algorithm.genomeLength <= MAX_DNA_LENGTH);
    fscanf(file, "Number of Populations: %d\n", &algorithm.numPopulations);
    fscanf(file, "Population Size: %d\n", &algorithm.populationSize);
    assert(algorithm.populationSize <= MAX_POPULATION_SIZE);
    
    fscanf(file, "Checkin Interval: %d\n", &algorithm.checkinInterval);
    fscanf(file, "Accuracy Cutoff: %lf\n", &algorithm.accuracyCutoff);
}
void saveManyPopulations(FILE *file){
    fprintf(file, "Genome Length: %d\n", algorithm.genomeLength);
    fprintf(file, "Number of Populations: %d\n", algorithm.numPopulations);
    fprintf(file, "Population Size: %d\n", algorithm.populationSize);
    
    fprintf(file, "Checkin Interval: %d\n", algorithm.checkinInterval);
    fprintf(file, "Accuracy Cutoff: %lf\n", algorithm.accuracyCutoff);
}

void printManyPopulationStatus(Population *p, int num);
void sortPops(Population *pops);

void runManyPopulations(FILE *file){
    int numPops = algorithm.numPopulations;
    int popSize = algorithm.populationSize;
    
    int populationIDCounter = 0;
    
    Timer timer = newTimer(0);
    //genomeData[i] points to the first element of the popSize Genomes in population i
    Genome *genomeData[numPops+1];
    Population pops[numPops+1];
    for (int i = 0; i < numPops; i++) {
        void *data = calloc(sizeof(Genome), popSize < 10 ? 10 : popSize);
        genomeData[i] = data;
        pops[i].genomes = genomeData[i];
        initializeRandomPopulation(&pops[i]);
        pops[i].ID = populationIDCounter++;
    }
    Genome *nextGenomeData = calloc(sizeof(Genome)*popSize, 1);
    
    
    int best = -1;
    for (int gen = 0; gen < MAX_GENERATION_COUNT; gen++) {
        
        for (int i = 0; i < numPops; i++) {
            for (int j = 0; j < popSize; j++) {
                if(strcmp(interpreter.name, "FastBF") == 0)
                    processGenome(&pops[i].genomes[j]);
                fitness.calculate(&pops[i].genomes[j]);
            }
            sortPopulation(&pops[i]);
            
            if(selector.copyElite)
                assert(pops[i].bestFitness == -1 || pops[i].bestFitness <= pops[i].sorted[0]->fitness);
            
            pops[i].bestFitness = pops[i].sorted[0]->fitness;
            if (pops[i].bestFitness > best) {
                best = pops[i].bestFitness;
                printf("New Best!\n");
                printManyPopulationStatus(&pops[i], i);
                
                updateTimer(&timer);
                printf("Time elapsed: %.2f\n", timer.totalTime);
                
                if(isRunningPng){
                    printf("\nBest:\n");
                    interpreter.print(&pops[i].sorted[0]->program);
                }
                
                if ((double)best/fitness.perfectFitness >= algorithm.accuracyCutoff) goto superbreak;
                
            }
        }
        
        if (gen % algorithm.checkinInterval == 0) {
            sortPops(pops);
            printf("\n");
            printf("Generation %d Check in:\n", gen);
            for (int i = numPops-1; i >= 0; i--) {
                printManyPopulationStatus(&pops[i], i);
            }
            printf("End Generation %d Check in\n\n", gen);
            updateTimer(&timer);
            printf("Time elapsed: %.2f\n", timer.totalTime);
            
            if(isRunningPng){
                printf("\nBest:\n");
                interpreter.print(&pops[0].sorted[0]->program);
            }
        }
        
        for (int i = 0; i < numPops; i++) {
            selector.prep(&pops[i]);
            for (int j = 0; j < popSize; j++) {
                Parents par = selector.select(&pops[i], j);
                if (par.p2 != NULL) {
                    breeder.breed(par.p1, par.p2, &nextGenomeData[j]);
                    mutator.mutate(&nextGenomeData[j]);
                    nextGenomeData[j].fitness = -1;
                }
                else{
                    nextGenomeData[j] = *par.p1;
                }
                if(strcmp(interpreter.name, "FastBF") != 0)
                    processGenome(&nextGenomeData[j]); //NOTE: NOT GOOD, CODE POINTS TO WRONG THING
            }
            
            memmove(pops[i].genomes, nextGenomeData, sizeof(Genome)*popSize);
            pops[i].generation++;
            
        }
    }
    
superbreak:
    
    sortPops(pops);
    printf("\n\n Final Results: \n");
    for (int i = numPops-1; i >= 0; i--) {
        printManyPopulationStatus(&pops[i], i);
    }
    
    updateTimer(&timer);
    printf("Time elapsed: %.2f\n\n", timer.totalTime);
    
    if(isRunningPng){
        printf("Final Best:\n");
        if(strcmp(interpreter.name, "BasicTree") == 0) interpreter.print(&pops[0].sorted[0]->program);
    }
    for (int i = numPops-1; i >= 0; i--) {
        free(genomeData[i]);
    }
    free(nextGenomeData);
    
}


void printManyPopulationStatus(Population *p, int num){
    
    
    printf("Population %d, ID %d, Generation %d, Best Fitness: %d/%d\n", num, p->ID, p->generation, p->bestFitness, fitness.perfectFitness);
    interpreter.print(&p->sorted[0]->program);
    printf("\nOutput: %s\n", p->sorted[0]->program.generic.output);
    //Code: %s\nOutput: %s\n", p->generation, p->sorted[0]->fitness, fitness.perfectFitness, p->sorted[0]->dna, p->sorted[0]->program.generic.output);
    printf("{");
    for (int i = 0; i < 15; i++) {
        printf("%d, ", (unsigned char)p->sorted[0]->program.generic.output[i]);
    }
    printf("}\n");
    printf("Code:\n");
    /*
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
    }*/
    
}


