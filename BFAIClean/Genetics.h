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
    Genome *genomes;
    //to avoid the in place sorting of tons of Genome structs (each very large), we just keep an array of pointers to elements and sort that array accordingly (initialize the array to have each pointer point to the corresponding genome then qsort
    Genome *sorted[MAX_POPULATION_SIZE];
    int bestFitness; //-1 if has not been calculated yet
    int ID;
    int generation;
} Population;




#endif /* Genetics_h */
