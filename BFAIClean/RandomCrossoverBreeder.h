//
//  RandomCrossoverBreeder.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef RandomCrossoverBreeder_h
#define RandomCrossoverBreeder_h

#include <stdio.h>
#include "Breeder.h"

/* Basic crossover algorithm where a random fraction f is chosen, and then the first f of child's genes
 are the first f of parent 1's genes, and the last (1-f) of child's genes are the last (1-f) of parent
 2's genes */

void initRandomCrossover(void);
void randomCrossoverBreed(Genome *p1, Genome *p2, Genome *child);
void scanRandomCrossover(FILE *file);
void saveRandomCrossover(FILE *file);

#endif /* RandomCrossoverBreeder_h */
