//
//  OysterInterpreter.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/28/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef OysterInterpreter_h
#define OysterInterpreter_h

#include "Interpreter.h"


#define OYSTER_MAX_LINE_COUNT 50

typedef struct _OysterProgram{
    GenericProgram generic;
    char *lines[OYSTER_MAX_LINE_COUNT];
} OysterProgram;


void initOysterInterpreter(void);
void scanOysterInterpreter(FILE *file);
void saveOysterInterpreter(FILE *file);
void processOysterInterpreter(char *code, OysterProgram *program);
int runOysterInterpreter(OysterProgram *program, char *input, int inputLen);

#endif /* OysterInterpreter_h */
