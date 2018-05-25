//
//  BasicTreeInterpreter.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef BasicTreeInterpreter_h
#define BasicTreeInterpreter_h

#include "Interpreter.h"

#define MAX_BT_OPS 100

/*
 BTOp chars:
 '0'-'9': load constant
 '+', '-', '*': binary arithmetic operations
 'x': load the input
 'k': kill the program -- all further commands return 0 [currently not in use]
 */
typedef struct _BTOp{
    char c;
    
    int parent;
    int children[2];
} BTOp;

typedef struct _BTProgram{
    GenericProgram generic;
    BTOp ops[MAX_BT_OPS];
    int len;
    
    int index; //for processing/running
    bool isDead;
} BTProgram;

void initBasicTreeInterpreter(void);
void scanBasicTreeInterpreter(FILE *file);
void saveBasicTreeInterpreter(FILE *file);
void processBasicTreeInterpreter(char *code, BTProgram *program);
int runBasicTreeInterpreter(BTProgram *program, char *input, int inputLen);


#endif /* BasicTreeInterpreter_h */
