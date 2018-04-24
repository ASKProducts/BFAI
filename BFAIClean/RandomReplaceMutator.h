//
//  RandomReplaceMutator.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef RandomReplaceMutator_h
#define RandomReplaceMutator_h

#include <stdio.h>
#include "Mutator.h"

/* Simple mutator that reads in mutationRate and then replaces one out of every mutationRate
 genes with a random gene from interpreter's validChars */

void initRandomReplace(void);
void randomReplaceMutate(Genome *g);
void scanRandomReplace(FILE *file);
void saveRandomReplace(FILE *file);

#endif /* RandomReplaceMutator_h */
