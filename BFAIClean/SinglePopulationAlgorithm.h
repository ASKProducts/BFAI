//
//  SinglePopulationAlgorithm.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef SinglePopulationAlgorithm_h
#define SinglePopulationAlgorithm_h

#include <stdio.h>
#include "Interpreter.h"

/* Basic overall strategy that uses one single population and advances it across generations */

void initSinglePopulation(void);
void runSinglePopulation(FILE *file);
void scanSinglePopulation(FILE *file);
void saveSinglePopulation(FILE *file);


#endif /* SinglePopulationAlgorithm_h */
