//
//  Interpreter.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

#include "Settings.h"
#include <stdbool.h>

typedef struct _GenericProgram {
    char *code;
    char output[PROGRAM_MAX_OUTPUT_LEN];
    unsigned int outputLen;
}GenericProgram;

typedef struct{
    GenericProgram generic;
    char padding[GENERIC_PROGRAM_PADDING];
} Program;

//A process func takes some code and a pointer to a GenericProgram and fills in the program with the data from the code
typedef void (*ProcessFunc) (char *code, Program *program);

//A run func takes in a program and a pointer to an array of input and runs it on that input, filling in that program's output as we go. (Maybe return the number of instructions?)
typedef void (*RunFunc) (Program *program, char *input, int inputLen);

//This allows the interpreter to scan whatever data is needs from the loadfile. Scan into the global variable interpreter.
typedef void (*ScanFunc) (FILE *file);

typedef struct _Interpreter{
    char *name; //Names must be only one token
    ProcessFunc process;
    RunFunc run;
    ScanFunc scan;
    
    char *validChars; //Interpreters can choose to scan this in or put it in init func
    bool isValid[256];
    
    int maxOutputLen;
    
    //The following properties can be dedicated to individual interpreters.
    
    /* Stupid Interpreter */
    int maxAs;
} Interpreter;


//Init functions do all their initializations into interpreters[numInterpreters], and at the end of
//the function must call numInterpreters++ and:
// assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING < sizeof( PROGRAM TYPE ));
typedef void (*InterpreterInitFunc) (void);

#endif /* Interpreter_h */
