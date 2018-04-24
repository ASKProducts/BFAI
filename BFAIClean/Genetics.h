//
//  Genetics.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Genetics_h
#define Genetics_h

#include <stdio.h>
#include "Settings.h"
#include "Interpreter.h"

typedef struct _Genome{
    char dna[MAX_DNA_LENGTH];
    Program program;
    int fitness; //-1 if the fitness has not been calculated
} Genome;

void processGenome(Genome *g);

//Populations will be allocated on the stack, and since population size is read in from the loadfile, we will just keep a pointer to the first element of the population, and initializing a population will consist of initializing its data on the stack and then linking a pointer.
typedef struct _Population{
    Genome *pop;
    int ID;
    int generation;
} Population;



#endif /* Genetics_h */
