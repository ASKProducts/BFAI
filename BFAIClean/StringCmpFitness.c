//
//  StringCmpFitness.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/25/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "StringCmpFitness.h"
#include <string.h>

extern FitnessFunction fitnessFuncs[];
extern FitnessFunction fitness;
extern int numFitnessFuncs;

extern Interpreter interpreter;

void initStringCmp(void){
    fitnessFuncs[numFitnessFuncs] = (FitnessFunction){
        .name = "StringCompare",
        .calculate = calculateStringCmpFitness,
        .scan = scanStringCmp,
        .save = saveStringCmp
    };
    numFitnessFuncs++;
    
}

void calculateStringCmpFitness(Genome *g){
    int score = 0;
    interpreter.run(&g->program, NULL, 0);
    int len = (fitness.targetLen < g->program.generic.outputLen) ? fitness.targetLen : g->program.generic.outputLen;
    for (int i = 0; i < len; i++) {
        int o1 = g->program.generic.output[i];
        int o2 = fitness.target[i];
        int v = o1 - o2;
        if(v < 0) v = -v;
        score += 256 - v;
        if(v != 0 && fitness.buildUpString) break;
    }
    if(fitness.targetLen == g->program.generic.outputLen)
        score += fitness.lengthReward;
    g->fitness = score;
}

void scanStringCmp(FILE *file){
    char target[1000];
    fgets(target, 1000, file);
    strcpy(fitness.target, target + strlen("Target String: "));
    int len = (int)strlen(fitness.target);
    fitness.target[len-1] = 0;
    fitness.targetLen = len-1;
    char c;
    fscanf(file, "Build Up String: %c\n", &c);
    fitness.buildUpString = (c == 'y');
    fscanf(file, "Length Reward: %d\n", &fitness.lengthReward);
}

void saveStringCmp(FILE *file){
    fprintf(file, "Target String: %s\n", fitness.target);
    fprintf(file, "Build Up String: %c\n", fitness.buildUpString ? 'y' : 'n');
    fprintf(file, "Length Reward: %d\n", fitness.lengthReward);
}
