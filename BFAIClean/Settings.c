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
#include <string.h>

InterpreterInitFunc initInterpreterFuncs[] = initFuncs;
Interpreter interpreters[10];
int numInterpreters = 0;
Interpreter interpreter;

void prepareInterpreter(FILE *file);

void initializeSettings(FILE *file){
    if(file == NULL) file = stdin;
    
    //Initialize each interpreter
    int numInitFuncs = sizeof(initInterpreterFuncs) / sizeof(InterpreterInitFunc);
    for (int i = 0; i < numInitFuncs; i++) {
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
    
    
    
}

void prepareInterpreter(FILE *file){
    interpreter.scan(file);
    
    char *c = interpreter.validChars;
    memset(interpreter.isValid, 0, 256);
    while(*c) {
        interpreter.isValid[*c] = true;
        c++;
    }
}
