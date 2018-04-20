//
//  FastBFInterpreter.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/20/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "FastBFInterpreter.h"
#include <assert.h>
#include <string.h>

extern Interpreter interpreters[];
extern Interpreter interpreter;
extern int numInterpreters;

void initFastBFInterpreter(void){
    interpreters[numInterpreters].name = "FastBF";
    interpreters[numInterpreters].process = (ProcessFunc)processFastBFInterpreter;
    interpreters[numInterpreters].run = (RunFunc)runFastBFInterpreter;
    interpreters[numInterpreters].scan = scanFastBFInterpreter;
    interpreters[numInterpreters].validChars = "+-><,.[]";
    numInterpreters++;
    
    assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING >= sizeof(FBFProgram));
}
void scanFastBFInterpreter(FILE *file){
    
}

#define advance(code) do{code++;}while(*code && !interpreter.isValid[*code])
void processFastBFInterpreter(char *code, FBFProgram *program){
    //int len = (int)strlen(code);
    program->generic.code = code;
    program->opCount = 0;
    
    int openStack[MAX_FBF_OPS];
    int openStackSize = 0;
    
    bool isBottom = true;
    int netShift = 0;
    int curInc = 0;
    
    while (*code && program->opCount < MAX_FBF_OPS) {
        char c = *code;
        switch (c) {
            case '+':
            case '-':
                program->ops[program->opCount].c = '+';
                int inc = 0;
                while (*code) {
                    if(*code == '+')inc++;
                    else if(*code == '-')inc--;
                    else break;
                    advance(code);
                }
                program->ops[program->opCount].val = inc;
                if(netShift == 0) curInc += inc;
                program->opCount++;
                break;
                
            case '>':
            case '<':
                program->ops[program->opCount].c = '>';
                int shift = 0;
                while (*code) {
                    if(*code == '>')shift++;
                    else if(*code == '<')shift--;
                    else break;
                    advance(code);
                }
                program->ops[program->opCount].val = shift;
                netShift += shift;
                program->opCount++;
                break;
                
            case '.':
            case ',':
                program->ops[program->opCount].c = c;
                program->opCount++;
                advance(code);
                break;
                
            case '[':
                openStack[openStackSize++] = program->opCount;
                isBottom = true;
                netShift = 0;
                curInc = 0;
                program->ops[program->opCount].c = '[';
                program->ops[program->opCount].val = -1;
                program->ops[program->opCount].isBalanced = false;
                advance(code);
                break;
                
            case ']':
                if(openStackSize == 0)goto bigbreak;
                int openIndex = openStack[--openStackSize];
                program->ops[openIndex].val = program->opCount;
                program->ops[program->opCount].val = openIndex;
                if(isBottom && netShift == 0){
                    program->ops[openIndex].isBalanced = true;
                    program->ops[openIndex].curInc = curInc;
                }
                break;
                
            default:
                break;
        }
    }
    
    bigbreak: curInc++;
    
}
void runFastBFInterpreter(FBFProgram *program, char *input, int inputLen){
    
}
