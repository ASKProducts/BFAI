//
//  TreeFunctionFitness.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "TreeFunctionFitness.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

extern FitnessFunction fitnessFuncs[];
extern FitnessFunction fitness;
extern int numFitnessFuncs;

extern Interpreter interpreter;

double targetFunction(double x){
    return atan(x);
}

void initTreeFuncFitness(void){
    fitnessFuncs[numFitnessFuncs++] = (FitnessFunction){
        .name = "TreeFunction",
        .calculate = calculateTreeFuncFitness,
        .scan = scanTreeFuncFitness,
        .save = saveTreeFuncFitness,
    };
    
}

//#define min(a,b) a<b?a:b
//#define max(a,b) a>b?a:b
#define abs(a) max(a, -a)

void calculateTreeFuncFitness(Genome *g){
    
    g->fitness = 0;
    g->program.generic.code = g->dna;
    /*for (int x = 0; x < 10; x++) {
        interpreter.run(&g->program, (char*)&x, 1);
        int res = *(int*)g->program.generic.output;
        int target = 6969;
        int dist = max(res-target, target-res);
        int m = min(dist, 2*target);
        g->fitness += m*10 / target;
    }*/
    
    for(int i = 0; i < fitness.numTestValues; i++){
        double x = fitness.testValues[i];
        
        int val = interpreter.run(&g->program, (char*)&x, 1);
        if(val == -1){
            g->fitness =0;
            return;
        }
        double res = *(double*)g->program.generic.output;
        double target = targetFunction(x);
        //int dist = max(res-target, target-res);
        //int m = min(dist, 2*target);
        double score = 0;
        int precision = fitness.precision;
        if(target < 0) {target = -target; res = -res;}
        if (res < 0) score = 0;
        else if (res <= target) score = (target == 0)? precision : res*precision/target;
        else if (res <= 2*target) score = (2*target - res)*precision/target;
        else score = 0;
        
        g->fitness += round(score);
    }
    
}
void scanTreeFuncFitness(FILE *file){
    //test values take one of two formats.
    //format 1:  range [start] [step] [count]
    //format 2: list [list of values]
    fscanf(file, "Precision: %d\n", &fitness.precision);
    
    char testValType[100];
    fscanf(file, "Test Values: %s", testValType);
    
    if (strcmp(testValType, "range") == 0) {
        fitness.testValType = 'r';
        double start, step; int count;
        fscanf(file, " %lf %lf %d\n", &start, &step, &count);
        fitness.testValStart = start;
        fitness.testValStep = step;
        for (int i = 0; i < count; i++) {
            fitness.testValues[i] = start + i*step;
        }
        fitness.numTestValues = count;
    }
    else{
        fitness.testValType = 'l';
        fitness.numTestValues = 0;
        char restOfLine[1000];
        char *str = restOfLine;
        fgets(restOfLine, 1000, file);
        restOfLine[strlen(restOfLine)-1] = 0;
        char *end = str;
        while(*end) {
            double n = strtod(str, &end);
            fitness.testValues[fitness.numTestValues++] = n;
            while (*end == ' ') {
                end++;
            }
            str = end;
        }
        
    }
    
    fitness.perfectFitness = fitness.numTestValues*fitness.precision;
    
}
void saveTreeFuncFitness(FILE *file){
    fprintf(file, "Precision: %d\n", fitness.precision);
    if(fitness.testValType == 'r')
        fprintf(file, "Test Values: range %.2lf %.2lf %d\n", fitness.testValStart, fitness.testValStep, fitness.numTestValues);
    else{
        fprintf(file, "Test Values: list");
        for (int i = 0; i < fitness.numTestValues; i++) {
            if(floor(fitness.testValues[i]) == fitness.testValues[i])
                fprintf(file, " %.0lf", fitness.testValues[i]);
            else
                fprintf(file, " %.2lf", fitness.testValues[i]);
        }
        fprintf(file, "\n");
    }
}
