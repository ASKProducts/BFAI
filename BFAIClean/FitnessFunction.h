//
//  FitnessFunction.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/25/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef FitnessFunction_h
#define FitnessFunction_h

#include <stdio.h>
#include "Genetics.h"

typedef void (*CalcFitnessFunc)(Genome *g);

#define MAX_TARGET_STRING 1000
#define MAX_NUM_TEST_VALUES 1000

typedef struct _FitnessFunction{
    char *name;
    
    CalcFitnessFunc calculate;
    ScanFunc scan;
    SaveFunc save;
    
    int perfectFitness;
    
    /* StringCompareFitness */
    char target[MAX_TARGET_STRING];
    int targetLen;
    bool buildUpString;
    int lengthReward;
    
    
    /* Addition */
    int start;
    int stop;
    int step;
    
    /* TreeFunctionFitness */
    double testValues[MAX_NUM_TEST_VALUES];
    int numTestValues;
    int precision;
    
    char testValType; //'r'==range, 'l'==list
    double testValStart, testValStep;
    double lengthPunishment;
    
} FitnessFunction;

#endif /* FitnessFunction_h */
