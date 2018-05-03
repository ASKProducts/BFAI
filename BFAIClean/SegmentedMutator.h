//
//  SegmentedMutator.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/30/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef SegmentedMutator_h
#define SegmentedMutator_h

#include "Mutator.h"

/* Same as ReplaceInsertMutator, except insertion mutations only affect the given segment. Uses SegmentedBreeder's segmentSize, so it relies on the usage of SegmentBreeder*/

void initSegmentMutator(void);
void segmentMutate(Genome *g);
void scanSegmentMutator(FILE *file);
void saveSegmentMutator(FILE *file);

#endif /* SegmentedMutator_h */
