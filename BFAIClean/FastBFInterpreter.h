//
//  FastBFInterpreter.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/20/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef FastBFInterpreter_h
#define FastBFInterpreter_h

#include "Interpreter.h"

#define MAX_FBF_OPS 500

//The fast-bf interpreter will make use of the fact that the memory max is explicitly 256. Other interpreters will be more versatile.
#define FBF_MEM_MAX 256

typedef struct _FBFOp{
    char c;
    short val;
    
    bool isBalanced;
    short netShift;
    short curInc;
} FBFOp;

typedef struct _FBFProgram{
    GenericProgram generic;
    FBFOp ops[MAX_FBF_OPS];
    int opCount;
} FBFProgram;


void initFastBFInterpreter(void);
void scanFastBFInterpreter(FILE *file);
void saveFastBFInterpreter(FILE *file);
void processFastBFInterpreter(char *code, FBFProgram *program);
int runFastBFInterpreter(FBFProgram *program, char *input, int inputLen);



#endif /* FastBFInterpreter_h */


/*
 Types of FBFOps:
 
 Inc:
 c = '+'
    val = amount to inc
 Shift:
    c = '<'
    val = amount to shift
 In:
    c = ','
 Out:
    c = '.'
 Loop:
    c = '['
    val = index of close
    isBalanced = is balanced?
    if balanced:
        curInc = amount that the current cell is incremented in this bloop
 EndLoop:
    c = ']'
    val = index of open
 */
