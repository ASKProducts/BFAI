//
//  SegmentBreeder.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/26/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//


#include "SegmentBreeder.h"
#include <stdlib.h>
#include <string.h>

extern Breeder breeders[];
extern Breeder breeder;
extern int numBreeders;

extern GeneticAlgorithm algorithm;

void initSegmentBreeder(void){
    breeders[numBreeders] = (Breeder){
        .name = "SegmentBreeder",
        .scan = scanSegmentBreeder,
        .save = saveSegmentBreeder,
        .breed = segmentBreed
    };
    numBreeders++;
}

void segmentBreed(Genome *p1, Genome *p2, Genome *child){
    int segSize = breeder.segmentSize;
    int genLen = algorithm.genomeLength;
    int i;
    for (i = 0; i + segSize < genLen; i += segSize) {
        if(rand() % 2 == 0)
            memmove(&child->dna[i], &p1->dna[i], segSize);
        else
            memmove(&child->dna[i], &p2->dna[i], segSize);
    }
    if(rand() % 2 == 0)
        memmove(&child->dna[i], &p1->dna[i], genLen - i);
    else
        memmove(&child->dna[i], &p2->dna[i], genLen - i);
}

void scanSegmentBreeder(FILE *file){
    fscanf(file, "Segment Size: %d\n", &breeder.segmentSize);
}

void saveSegmentBreeder(FILE *file){
    fprintf(file, "Segment Size: %d\n", breeder.segmentSize);
}
