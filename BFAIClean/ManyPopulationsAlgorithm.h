//
//  ManyPopulationsAlgorithm.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/14/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef ManyPopulationsAlgorithm_h
#define ManyPopulationsAlgorithm_h

#include <stdio.h>
#include "Interpreter.h"

/* Overall Strategy that runs many populations simultaneiously */

void initManyPopulations(void);
void runManyPopulations(FILE *file);
void scanManyPopulations(FILE *file);
void saveManyPopulations(FILE *file);

#endif /* ManyPopulationsAlgorithm_h */
