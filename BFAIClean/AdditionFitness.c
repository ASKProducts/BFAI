//
//  AdditionFitness.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "AdditionFitness.h"

extern FitnessFunction fitnessFuncs[];
extern FitnessFunction fitness;
extern int numFitnessFuncs;

extern Interpreter interpreter;

void initAdditionFitness(void){
    fitnessFuncs[numFitnessFuncs] = (FitnessFunction){
        .name = "Addition",
        .calculate = calculateAdditionFitness,
        .scan = scanAdditionFitness,
        .save = saveAdditionFitness
    };
    numFitnessFuncs++;
}
void calculateAdditionFitness(Genome *g){
    int score = 0;
    for (int i = 10; i < 60; i+= 10) {
        for (int j = 10; j < 60; j+= 10) {
            char input[] = {i,j};
            interpreter.run(&g->program, input, 2);
            if(g->program.generic.outputLen != 1) continue;
            score += (g->program.generic.output[0] == (i+j));
        }
    }
    g->fitness = score;
}
void scanAdditionFitness(FILE *file){
    
}
void saveAdditionFitness(FILE *file){
    
}
