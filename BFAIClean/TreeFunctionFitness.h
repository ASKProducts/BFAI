//
//  TreeFunctionFitness.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef TreeFunctionFitness_h
#define TreeFunctionFitness_h

#include "FitnessFunction.h"

void initTreeFuncFitness(void);
void calculateTreeFuncFitness(Genome *g);
void scanTreeFuncFitness(FILE *file);
void saveTreeFuncFitness(FILE *file);

#endif /* TreeFunctionFitness_h */
