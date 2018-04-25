//
//  Settings.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "Settings.h"
#include "Interpreter.h"
#include "StupidInterpreter.h"
#include "FastBFInterpreter.h"
#include "SinglePopulationAlgorithm.h"
#include "RandomCrossoverBreeder.h"
#include "Mutator.h"
#include "Algorithm.h"
#include "Breeder.h"
#include "RandomReplaceMutator.h"
#include "BreedingSelector.h"
#include "BreedTop.h"
#include <string.h>

InitFunc initInterpreterFuncs[] = interpreterInits;
Interpreter interpreters[30];
int numInterpreters = 0;
Interpreter interpreter;

InitFunc initAlgorithmFuncs[] = algorithmInits;
GeneticAlgorithm algorithms[30];
int numAlgorithms = 0;
GeneticAlgorithm algorithm;

InitFunc initBreederFuncs[] = breederInits;
Breeder breeders[30];
int numBreeders = 0;
Breeder breeder;

InitFunc initMutatorFuncs[] = mutatorInits;
Mutator mutators[30];
int numMutators = 0;
Mutator mutator;

InitFunc initSelectorFuncs[] = selectorInits;
BreedingSelector selectors[30];
int numSelectors = 0;
BreedingSelector selector;




FILE *loadfile;

inline void prepareInterpreter(FILE *file);
inline void prepareAlgorithm(FILE *file);
inline void prepareBreeder(FILE *file);
inline void prepareMutator(FILE *file);
inline void prepareSelector(FILE *file);

void initializeSettings(FILE *file){
    if(file == NULL) file = stdin;
    loadfile = file;
    //Initialize each interpreter
    
    /****** INTERPRETERS *****/
    int numInterpreterInits = sizeof(initInterpreterFuncs) / sizeof(InitFunc);
    for (int i = 0; i < numInterpreterInits; i++) {
        initInterpreterFuncs[i]();
    }
    
    char interpreterName[100];
    fscanf(file, "Interpreter: %s\n", interpreterName);
    for (int i = 0; i < numInterpreters; i++) {
        if(strcmp(interpreterName, interpreters[i].name) == 0){
            interpreter = interpreters[i];
            prepareInterpreter(file);
            break;
        }
    }
    
    /****** ALGORITHMS *****/
    int numAlgoInits = sizeof(initAlgorithmFuncs) / sizeof(InitFunc);
    for (int i = 0; i < numAlgoInits; i++) {
        initAlgorithmFuncs[i]();
    }
    char algorithmName[100];
    fscanf(file, "Algorithm: %s\n", algorithmName);
    for (int i = 0; i < numAlgorithms; i++) {
        if(strcmp(algorithmName, algorithms[i].name) == 0){
            algorithm = algorithms[i];
            prepareAlgorithm(file);
            break;
        }
    }
    
    
    /****** BREEDERS *****/
    int numBreederInits = sizeof(initBreederFuncs) / sizeof(InitFunc);
    for (int i = 0; i < numBreederInits; i++) {
        initBreederFuncs[i]();
    }
    char breederName[100];
    fscanf(file, "Breeder: %s\n", breederName);
    for (int i = 0; i < numBreeders; i++) {
        if(strcmp(breederName, breeders[i].name) == 0){
            breeder = breeders[i];
            prepareBreeder(file);
            break;
        }
    }
    
    /****** MUTATORS *****/
    int numMutatorInits = sizeof(initMutatorFuncs) / sizeof(InitFunc);
    for (int i = 0; i < numMutatorInits; i++) {
        initMutatorFuncs[i]();
    }
    char mutatorName[100];
    fscanf(file, "Mutator: %s\n", mutatorName);
    for (int i = 0; i < numMutators; i++) {
        if(strcmp(mutatorName, mutators[i].name) == 0){
            mutator = mutators[i];
            prepareMutator(file);
            break;
        }
    }
    
    
    /****** SELECTORS *****/
    int numSelectorInits = sizeof(initSelectorFuncs) / sizeof(InitFunc);
    for (int i = 0; i < numSelectorInits; i++) {
        initSelectorFuncs[i]();
    }
    char selectorName[100];
    fscanf(file, "Breeding Selector: %s\n", selectorName);
    for (int i = 0; i < numSelectors; i++) {
        if(strcmp(selectorName, selectors[i].name) == 0){
            selector = selectors[i];
            prepareSelector(file);
            break;
        }
    }
    
    
    
}

void prepareInterpreter(FILE *file){
    interpreter.scan(file);
    
    char *c = interpreter.validChars;
    interpreter.numValidChars = (int)strlen(c);
    memset(interpreter.isValid, 0, 256);
    while(*c) {
        interpreter.isValid[*c] = true;
        c++;
    }
}

void prepareAlgorithm(FILE *file){
    algorithm.scan(file);
}

void prepareBreeder(FILE *file){
    algorithm.scan(file);
}

void prepareMutator(FILE *file){
    mutator.scan(file);
}

void prepareSelector(FILE *file){
    selector.scan(file);
}





void saveSettings(){
    fprintf(loadfile, "Interpreter: %s\n", interpreter.name);
    interpreter.save(loadfile);
    fprintf(loadfile, "Algorithm: %s\n", algorithm.name);
    algorithm.save(loadfile);
    fprintf(loadfile, "Breeder: %s\n", breeder.name);
    breeder.save(loadfile);
    fprintf(loadfile, "Mutator: %s\n", mutator.name);
    mutator.save(loadfile);
    fprintf(loadfile, "Breeding Selector: %s\n", mutator.name);
    mutator.save(loadfile);
    
}


