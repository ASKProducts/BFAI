//
//  RandomReplaceMutator.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "RandomReplaceMutator.h"
#include "Algorithm.h"

#include <stdlib.h>

extern Mutator mutators[];
extern Mutator mutator;
extern int numMutators;

extern GeneticAlgorithm algorithm;

extern Interpreter interpreter;

void initRandomReplace(void){
    mutators[numMutators].name = "RandomReplace";
    mutators[numMutators].mutate = randomReplaceMutate;
    mutators[numMutators].scan = scanRandomReplace;
    mutators[numMutators].save = saveRandomReplace;
    
    numMutators++;
}

void randomReplaceMutate(Genome *g){
    int len = algorithm.genomeLength;
    int mutationRate = mutator.mutationRate;
    char *validChars = interpreter.validChars;
    int numValidChars = interpreter.numValidChars;
    
    for (int i = 0; i < len; i++) {
        int r = rand() % mutationRate;
        if (r == 0){
            int r2 = rand() % numValidChars;
            g->dna[i] = validChars[r2];
        }
    }
}

void scanRandomReplace(FILE *file){
    fscanf(file, "Mutation Rate: %d\n", &mutator.mutationRate);
}

void saveRandomReplace(FILE *file){
    fprintf(file, "Mutation Rate: %d\n", mutator.mutationRate);
}
