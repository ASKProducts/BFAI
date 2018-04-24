//
//  main.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include <stdio.h>
#include "Settings.h"
#include "Interpreter.h"
#include "StupidInterpreter.h"
#include "FastBFInterpreter.h"
#include "Algorithm.h"
#include <stdlib.h>
#include <time.h>
#include "Genetics.h"
#include "Mutator.h"
#include "Breeder.h"

extern Interpreter interpreter;
extern GeneticAlgorithm algorithm;
extern Mutator mutator;
extern Breeder breeder;

/*
 Key components of genetic algorithm:
 
 . interpreter
 . breeding method (current convention: breeder algorithm just breeds dna, strategy processes genome -- this makes sense because mutations still need to happen)
 . mutation method
 breeding selection method
 fitness function
 . overarching strategy
 */

int main(int argc, const char * argv[]) {
    srand((int)time(NULL));
    
    FILE *file = fopen("./BasicTest.lf", "rw");
    initializeSettings(file);
    
    Program p;
    interpreter.process(",[.,]", &p);
    interpreter.run(&p, "Hello World!", 12);
    printf("%s\n", p.generic.output);
    
    Genome g, g2, c1, c2;
    for (int i = 0; i < algorithm.genomeLength; i++) {
        g.dna[i] = '+';
        g2.dna[i] = '-';
    }
    g.dna[algorithm.genomeLength]=0;
    g2.dna[algorithm.genomeLength]=0;
    c1.dna[algorithm.genomeLength]=0;
    c2.dna[algorithm.genomeLength]=0;
    
    breeder.breed(&g,&g2 ,&c1);
    breeder.breed(&g,&g2, &c2);
    printf("\n%s\n\n%s\n", c1.dna, c2.dna);

    
    return 0;
}
