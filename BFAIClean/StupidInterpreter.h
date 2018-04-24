//
//  StupidInterpreter.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef StupidInterpreter_h
#define StupidInterpreter_h
#include "Interpreter.h"

typedef struct _SIProgram{
    GenericProgram generic;
    int numberOfAs;
} SIProgram;

//Stupid interpreter that computes the number of As in the input and code, adds them together, and outputs that number. If that number exceeds the interpreter's MaxAs, then it outputs maxAs.
void initStupidInterpreter(void);
void saveStupidInterpreter(FILE *file);
void scanStupidInterpreter(FILE *file);
void processStupidInterpreter(char *code, SIProgram *program);
void runStupidInterpreter(SIProgram *program, char *input, int inputLen);


#endif /* StupidInterpreter_h */
