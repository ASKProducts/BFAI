//
//  ReplaceInsertMutator.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "ReplaceInsertMutator.h"
#include "Algorithm.h"

#include <stdlib.h>
#include <string.h>

extern Mutator mutators[];
extern Mutator mutator;
extern int numMutators;

extern GeneticAlgorithm algorithm;

extern Interpreter interpreter;

void initReplaceInsert(void){
    mutators[numMutators].name = "ReplaceInsert";
    mutators[numMutators].mutate = replaceInsertMutate;
    mutators[numMutators].scan = scanReplaceInsert;
    mutators[numMutators].save = saveReplaceInsert;
    
    numMutators++;
}
void replaceInsertMutate(Genome *g){
    int len = algorithm.genomeLength;
    int mutationRate = mutator.mutationRate;
    char *AIChars = interpreter.AIChars;
    int numAIChars = interpreter.numAIChars;
    
    for (int i = 0; i < len; i++) {
        int r = rand() % mutationRate;
        if (r == 0){
            int r2 = rand() % (numAIChars + 1);
            if(r2 == numAIChars){ //insert
                memcpy(&g->dna[i] + 1, &g->dna[i], len - i - 1);
                int r3 = rand() % (numAIChars);
                g->dna[i] = AIChars[r3];
            }
            else //replace
                g->dna[i] = AIChars[r2];
        }
    }
}
void scanReplaceInsert(FILE *file){
    fscanf(file, "Mutation Rate: %d\n", &mutator.mutationRate);
}
void saveReplaceInsert(FILE *file){
    fprintf(file, "Mutation Rate: %d\n", mutator.mutationRate);
}
