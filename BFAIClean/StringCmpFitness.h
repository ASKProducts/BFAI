//
//  StringCmpFitness.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/25/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef StringCmpFitness_h
#define StringCmpFitness_h

#include "FitnessFunction.h"

void initStringCmp(void);
void calculateStringCmpFitness(Genome *g);
void scanStringCmp(FILE *file);
void saveStringCmp(FILE *file);

#endif /* StringCmpFitness_h */
