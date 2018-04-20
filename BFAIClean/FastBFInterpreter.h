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

typedef struct _FBFOp{
    char c;
    int val;
    
    bool isBalanced;
    int netShift;
    int curInc;
} FBFOp;

typedef struct _FBFProgram{
    GenericProgram generic;
    FBFOp ops[MAX_FBF_OPS];
    int opCount;
} FBFProgram;

//Stupid interpreter that computes the number of As in the input and code, adds them together, and outputs that number. If that number exceeds the interpreter's MaxAs, then it outputs maxAs.
void initFastBFInterpreter(void);
void scanFastBFInterpreter(FILE *file);
void processFastBFInterpreter(char *code, FBFProgram *program);
void runFastBFInterpreter(FBFProgram *program, char *input, int inputLen);



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
