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
#include "FitnessFunction.h"
#include <string.h>

extern Interpreter interpreter;
extern GeneticAlgorithm algorithm;
extern Mutator mutator;
extern Breeder breeder;
extern FitnessFunction fitness;

/*
 Key components of genetic algorithm:
 
 . interpreter
 . breeding method (current convention: breeder algorithm just breeds dna, strategy processes genome -- this makes sense because mutations still need to happen)
 . mutation method
 . breeding selection method
 fitness function
 . overarching strategy
 */

const char *loadfileName;
bool isRunningPng = false;

int main(int argc, const char * argv[]) {
    srand((int)time(NULL));
    
    if(argc == 3 && strcmp(argv[2], "-p") == 0)isRunningPng = true;
    
    loadfileName = argv[1];
    
    FILE *file = fopen(loadfileName, "r");
    initializeSettings(file);
    
    /*
    Program p;
    interpreter.process("-/ *x*-**+*56+293x+87xx/9*80", &p);
    double inputs[] = {1,2,3,4,5};
    for (int i = 0; i < 5; i++) {
        int ret = interpreter.run(&p, (char*)&inputs[i], 1);
        printf("%d\n", *(int*)p.generic.output);
    }
    return 0;*/
    
    /*Program p;
    interpreter.process("JFI++.H<FGD+IBDJ>.D.-DBF-.GAID"
                        "J-ADDF+-HIIJ>-+JG-IDIGIGE<,FHF"
                        ",HG<FD++>FA,DJBEJJHHHEEFJHD,.."
                        ",A>+D,FEJFBFAG<DAA<BH>E>EJ.FHF"
                        "+,J<FBJBD.AD>GFA..I+EE<GD-,>D,"
                        "EH,HA--HJ-<E+D>+EJII-+H<<EB.FB"
                        "HH>HDF>F>+-F><DIBGDEA-.<-I+<-I"
                        "..J-H-DAF-I,DBEFF.IJI<G.J+,+GI"
                        "+EE.++D.B.HJFDFEI,IGA.J>I+.E<J"
                        ",.EG.FHGDHD+D.>E<+>>,DHG<F>DJ.", &p);
    interpreter.run(&p, "Hello World!", 12);
    printf("%s\n", p.generic.output);*/
    
    /*
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
    */
    /*
    Genome ge;
    strcpy(ge.dna, ",[--[+[--[,++++..<-],+++.>.-],+.],++.],.");
    processGenome(&ge);
    
    char input[] = {3,4};
    interpreter.run(&ge.program, input, 2);
    printf("%d\n", ge.program.generic.output[0]);
    
    fitness.calculate(&ge);*/
    
    algorithm.run(file);
    
    
    
    //saveSettings();

    fclose(file);
    return 0;
}
