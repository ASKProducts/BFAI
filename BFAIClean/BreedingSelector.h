//
//  BreedingSelector.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef BreedingSelector_h
#define BreedingSelector_h

#include <stdio.h>
#include "Interpreter.h"
#include "Genetics.h"

typedef struct _Parents{
    Genome *p1;
    Genome *p2;
} Parents;

//BreedSelectPrepFunc does any necessary preprocessing (other than sorting, which the genetic algorithm is responsible for.) For example, computing a table of fitnesses for roulette selection.
typedef void (*BreedSelectPrepFunc)(Population *p);

//A BreedSelect func takes population and a child number to make and returns a pair of parents to breed. If the two parents are the same, the parent should just be copied
typedef Parents (*BreedSelectFunc)(Population *p, int childNum);


typedef struct _BreedingSelector{
    char *name;
    
    BreedSelectFunc select;
    BreedSelectPrepFunc prep;
    ScanFunc scan;
    SaveFunc save;
    
    //for BreedTop
    int elitePercentage;
    bool copyElite;
    
} BreedingSelector;

#endif /* BreedingSelector_h */
