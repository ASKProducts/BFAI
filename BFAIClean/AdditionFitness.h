//
//  AdditionFitness.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef AdditionFitness_h
#define AdditionFitness_h

#include "FitnessFunction.h"

void initAdditionFitness(void);
void calculateAdditionFitness(Genome *g);
void scanAdditionFitness(FILE *file);
void saveAdditionFitness(FILE *file);

#endif /* AdditionFitness_h */
