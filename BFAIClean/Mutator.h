//
//  Mutator.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Mutator_h
#define Mutator_h

#include <stdio.h>
#include "Genetics.h"
#include "Settings.h"

typedef void (*MutateFunc)(Genome *g);

typedef struct _Mutator{
    char *name;
    
    MutateFunc mutate;
    ScanFunc scan;
    SaveFunc save;
    
    int mutationRate;
} Mutator;

#endif /* Mutator_h */
