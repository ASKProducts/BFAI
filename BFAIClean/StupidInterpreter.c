//
//  StupidInterpreter.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "StupidInterpreter.h"
#include "Interpreter.h"
#include <string.h>
#include <assert.h>

extern Interpreter interpreters[];
extern Interpreter interpreter;
extern int numInterpreters;

void initStupidInterpreter(){
    interpreters[numInterpreters].name = "StupidInterpreter";
    interpreters[numInterpreters].process = (ProcessFunc)processStupidInterpreter;
    interpreters[numInterpreters].run = (RunFunc)runStupidInterpreter;
    interpreters[numInterpreters].scan = scanStupidInterpreter;
    interpreters[numInterpreters].save = saveStupidInterpreter;
    interpreters[numInterpreters].validChars = "ABCDE";
    numInterpreters++;
    
    assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING >= sizeof(SIProgram));
}

/*
 Scan Format:
 MaxAs: [MaxAs]
 */
void scanStupidInterpreter(FILE *file){
    fscanf(file, "Max As: %d\n", &interpreter.maxAs);
}

void saveStupidInterpreter(FILE *file){
    fprintf(file, "Max As: %d\n", interpreter.maxAs);
}

void processStupidInterpreter(char *code, SIProgram *program){
    program->generic.code = code;
    program->numberOfAs = 0;
    int len = (int)strlen(code);
    for (int i = 0; i < len; i++) {
        if(code[i] == 'A'){
            program->numberOfAs++;
        }
    }
}

void runStupidInterpreter(SIProgram *program, char *input, int inputLen){
    int As = program->numberOfAs;
    for (int i = 0; i < inputLen; i++) {
        if(input[i] == 'A')As++;
    }
    if(As > interpreter.maxAs) As = interpreter.maxAs;
    sprintf(program->generic.output, "Number of As is: %d", As);
    program->generic.outputLen = (int)strlen(program->generic.output);
}
