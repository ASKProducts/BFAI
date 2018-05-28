//
//  SegmentBreeder.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef TreeBreeder_h
#define TreeBreeder_h

#include "Breeder.h"

/* Breeds two genomes by choosing a random index and swapping the trees rooted at those indices */

void initTreeBreeder(void);
void treeBreed(Genome *p1, Genome *p2, Genome *child);
void scanTreeBreeder(FILE *file);
void saveTreeBreeder(FILE *file);

#endif /* TreeBreeder_h */
