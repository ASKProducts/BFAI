//
//  SegmentBreeder.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef SegmentBreeder_h
#define SegmentBreeder_h

#include "Breeder.h"

/* Breed's two genomes by randomly choosing segments of size breeder.segmentSize length from either parent */

void initSegmentBreeder(void);
void segmentBreed(Genome *p1, Genome *p2, Genome *child);
void scanSegmentBreeder(FILE *file);
void saveSegmentBreeder(FILE *file);

#endif /* SegmentBreeder_h */
