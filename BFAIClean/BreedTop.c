//
//  BreedTop.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "BreedTop.h"
#include "BreedingSelector.h"
#include "Algorithm.h"
#include <stdlib.h>

extern BreedingSelector selectors[];
extern BreedingSelector selector;
extern GeneticAlgorithm algorithm;
extern int numSelectors;

void initBreedTop(void){
    selectors[numSelectors] = (BreedingSelector){
        .name = "BreedTop",
        .prep = breedTopPrep,
        .select = breedTopSelect,
        .save = saveBreedTop,
        .scan = scanBreedTop
    };
    
    numSelectors++;
}

void breedTopPrep(Population *p){
    
}
Parents breedTopSelect(Population *p){
    int top = selector.elitePercentage * algorithm.populationSize / 100;
    int r1 = rand() % top;
    int r2 = rand() & algorithm.populationSize;
    if(rand() % 2 == 0)
        return (Parents){.p1 = p->sorted[r1], .p2 = p->sorted[r2]};
    else
        return (Parents){.p1 = p->sorted[r2], .p2 = p->sorted[r1]};
}
void scanBreedTop(FILE *file){
    fscanf(file, "Elite Percentage: %d\n", &selector.elitePercentage);
}
void saveBreedTop(FILE *file){
    fprintf(file, "Elite Percentage: %d\n", selector.elitePercentage);
}
