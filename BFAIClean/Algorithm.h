//
//  Algorithm.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Algorithm_h
#define Algorithm_h

#include <stdio.h>
#include "Interpreter.h"

typedef void (*GeneticAlgorithmRunFunc)(FILE *loadfile);


typedef struct _GeneticAlgorithm{
    char *name;
    GeneticAlgorithmRunFunc run;
    
    ScanFunc scan;
    SaveFunc save;
    
    int genomeLength;
    int populationSize;
    
    //Many populations
    int numPopulations;
    int checkinInterval;
    
} GeneticAlgorithm;


#endif /* Algorithm_h */
