//
//  ReplaceInsertMutator.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef ReplaceInsertMutator_h
#define ReplaceInsertMutator_h

#include <stdio.h>
#include "Mutator.h"

/* Simple mutator that reads in mutationRate and then either replaces one out of every mutationRate
 genes with a random gene from interpreter's validChars or inserts a gene into it*/

void initReplaceInsert(void);
void replaceInsertMutate(Genome *g);
void scanReplaceInsert(FILE *file);
void saveReplaceInsert(FILE *file);

#endif /* ReplaceInsertMutator_h */
