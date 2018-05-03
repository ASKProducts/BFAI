//
//  SegmentedMutator.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/30/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "SegmentedMutator.h"
#include "Algorithm.h"
#include "Breeder.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

extern Mutator mutators[];
extern Mutator mutator;
extern int numMutators;

extern GeneticAlgorithm algorithm;
extern Breeder breeder;

extern Interpreter interpreter;

void initSegmentMutator(void){
    mutators[numMutators] = (Mutator){
        .name = "SegmentMutator",
        .mutate = segmentMutate,
        .scan = scanSegmentMutator,
        .save = saveSegmentMutator
    };
    numMutators++;
}


void segmentMutate(Genome *g){
    int len = algorithm.genomeLength;
    int mutationRate = mutator.mutationRate;
    char *AIChars = interpreter.AIChars;
    int numAIChars = interpreter.numAIChars;
    int segSize = breeder.segmentSize;
    
    for (int i = 0; i < len; i++) {
        int r = rand() % mutationRate;
        if (r == 0){
            int r2 = rand() % (numAIChars + 1);
            if(r2 == numAIChars){ //insert
                int currentSeg = i/segSize;
                int end = min((currentSeg+1) * segSize, len);
                memcpy(&g->dna[i] + 1, &g->dna[i], end - i - 1);
                int r3 = rand() % (numAIChars);
                g->dna[i] = AIChars[r3];
            }
            else //replace
                g->dna[i] = AIChars[r2];
        }
    }
}
void scanSegmentMutator(FILE *file){
    fscanf(file, "Mutation Rate: %d\n", &mutator.mutationRate);
    assert(strcmp("SegmentBreeder", breeder.name) == 0);
}
void saveSegmentMutator(FILE *file){
    fprintf(file, "Mutation Rate: %d\n", mutator.mutationRate);
}
