//
//  Genetics.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "Genetics.h"
#include "Algorithm.h"
#include <stdlib.h>

extern Interpreter interpreter;
extern GeneticAlgorithm algorithm;

void processGenome(Genome *g){
    interpreter.process(g->dna, &g->program);
}

void initializeRandomGenome(Genome *g){
    int len = algorithm.genomeLength;
    int numChars = interpreter.numAIChars;
    for (int i = 0; i < len; i++) {
        int r = rand() % numChars;
        g->dna[i] = interpreter.AIChars[r];
    }
    g->dna[len] = 0;
    g->fitness = -1;
}

//TODO: new IDs
void initializeRandomPopulation(Population *p){
    p->generation = 0;
    p->bestFitness  =-1;
    int popSize = algorithm.populationSize;
    for (int i = 0; i < popSize; i++) {
        initializeRandomGenome(&p->genomes[i]);
        processGenome(&p->genomes[i]);
        p->sorted[i] = &p->genomes[i];
    }
}

int genomeCmp(const void *g1, const void *g2){
    Genome *l = *(Genome**)g1;
    Genome *r = *(Genome**)g2;
    return r->fitness - l->fitness;
}

void sortPopulation(Population *p){
    qsort(p->sorted, algorithm.populationSize, sizeof(Genome*), genomeCmp);
}






