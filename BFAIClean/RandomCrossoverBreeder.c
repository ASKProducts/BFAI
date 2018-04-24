//
//  RandomCrossoverBreeder.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "RandomCrossoverBreeder.h"
#include <stdlib.h>

extern Breeder breeders[];
extern Breeder breeder;
extern int numBreeders;

extern GeneticAlgorithm algorithm;

void initRandomCrossover(void){
    breeders[numBreeders].name = "RandomCrossover";
    breeders[numBreeders].breed = randomCrossoverBreed;
    breeders[numBreeders].scan = scanRandomCrossover;
    breeders[numBreeders].save = saveRandomCrossover;
    
    numBreeders++;
}

void randomCrossoverBreed(Genome *p1, Genome *p2, Genome *child){
    int genomeLen = algorithm.genomeLength;
    int numP1 = rand() % genomeLen;
    for (int i = 0; i < numP1; i++) {
        child->dna[i] = p1->dna[i];
    }
    for (int i = numP1; i < genomeLen; i++) {
        child->dna[i] = p2->dna[i];
    }
}

void scanRandomCrossover(FILE *file){
    
}

void saveRandomCrossover(FILE *file){
    
}
