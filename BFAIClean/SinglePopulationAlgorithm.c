//
//  SinglePopulationAlgorithm.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "SinglePopulationAlgorithm.h"
#include "Algorithm.h"
#include "Genetics.h"

extern GeneticAlgorithm algorithms[];
extern GeneticAlgorithm algorithm;
extern int numAlgorithms;

void initSinglePopulation(void){
    algorithms[numAlgorithms].name = "SinglePopulation";
    algorithms[numAlgorithms].run = runSinglePopulation;
    algorithms[numAlgorithms].save = saveSinglePopulation;
    algorithms[numAlgorithms].scan = scanSinglePopulation;
    
    numAlgorithms++;
}

void scanSinglePopulation(FILE *file){
    fscanf(file, "Genome Length: %d\n", &algorithm.genomeLength);
    fscanf(file, "Population Size: %d\n", &algorithm.populationSize);
}
void saveSinglePopulation(FILE *file){
    fprintf(file, "Genome Length: %d\n", algorithm.genomeLength);
    fprintf(file, "Population Size: %d\n", algorithm.populationSize);
}

void runSinglePopulation(FILE *file){
    
}




