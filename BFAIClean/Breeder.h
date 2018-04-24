//
//  Breeder.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/23/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Breeder_h
#define Breeder_h

#include "Algorithm.h"
#include "Genetics.h"

typedef void (*BreedFunc)(Genome *p1, Genome *p2, Genome *child);

typedef struct _Breeder{
    char *name;
    
    ScanFunc scan;
    SaveFunc save;
    
    BreedFunc breed;
    
}Breeder;

#endif /* Breeder_h */
