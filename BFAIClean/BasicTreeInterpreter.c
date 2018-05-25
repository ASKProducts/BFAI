//
//  BasicTreeInterpreter.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "BasicTreeInterpreter.h"
#include <assert.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

extern Interpreter interpreters[];
extern Interpreter interpreter;
extern int numInterpreters;

int arity[256];

void initBasicTreeInterpreter(void){
    interpreters[numInterpreters++] = (Interpreter){
        .name = "BasicTree",
        .scan = scanBasicTreeInterpreter,
        .save = saveBasicTreeInterpreter,
        .process = (ProcessFunc)processBasicTreeInterpreter,
        .run = (RunFunc)runBasicTreeInterpreter
    };
    
    assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING >= sizeof(BTProgram));
    
    for (int i = 0; i < 9; i++) {
        arity['0' + i] = 0;
    }
    arity['p'] = 0;
    arity['x'] = 0;
    arity['k'] = 0;
    
    arity['+'] = 2;
    arity['-'] = 2;
    arity['*'] = 2;
    arity['/'] = 2;
    arity['^'] = 2;
    
    arity['E'] = 1;
    arity['L'] = 1;
}
void scanBasicTreeInterpreter(FILE *file){
    fscanf(file, "Operators: %s\n", interpreter.operators);
    fscanf(file, "Constants: %s\n", interpreter.constants);
    
    interpreter.validChars = malloc(100);
    sprintf(interpreter.validChars, "%s%s", interpreter.operators, interpreter.constants);
    interpreter.AIChars = interpreter.validChars;
    
    //interpreter.validChars = "0123456789+-*x";
    //interpreter.AIChars = "4+-*x";
}
void saveBasicTreeInterpreter(FILE *file){
    fprintf(file, "Operators: %s\n", interpreter.operators);
    fprintf(file, "Constants: %s\n", interpreter.constants);
}

void process(BTProgram *program){
    if(program->index >= program->len){
        //we've reached the end. just return?
        return;
    }
    
    BTOp *curOp = &program->ops[program->index];
    char curC = program->generic.code[program->index];
    curOp->c = curC;
    program->index++;
    
    if(arity[curC] == 0) return;
    

    
}

void processBasicTreeInterpreter(char *code, BTProgram *program){
    program->generic.code = code;
    
    size_t len = strlen(code);
    program->len = (int)len;
    return;
//    int index = 0;
//    while (index < len) {
//
//    }
    
}

double evaluate(BTProgram *program, double x){
    if(program->isDead || program->index >= program->len) return 0;
    
    char c = program->generic.code[program->index++];
    
    if (arity[c] == 0) {
        if(c >= '0' && c <= '9') return c - '0';
        if(c == 'p') return M_PI;
        if(c == 'x') return x;
        if (c == 'k') {
            program->isDead = true;
            return 0;
        }
    }
    else if (arity[c] == 1){
        double val = evaluate(program, x);
        if (c == 'E')
            return exp(val);
        else if (c == 'L'){
            if (val <= 0){
                program->isDead = true;
                return 0;
            }
            return log(val);
        }
    }
    else if (arity[c] == 2){
        double val1 = evaluate(program, x);
        double val2 = evaluate(program, x);
        if (c == '+')
            return val1+val2;
        else if (c == '-')
            return val1-val2;
        else if (c == '*')
            return val1*val2;
        else if (c == '/'){
            if (val2 == 0) {
                program->isDead = true;
                return 0;
            }
            else return val1/val2;
        }
        else if (c == '^'){
            if (val1 <= 0) {
                program->isDead = true;
                return 0;
            }
            else return pow(val1, val2);
        }
    }
    
   //     return val2 == 0 || val2 == INT_MIN || val1 == INT_MIN ? INT_MAX : val1/val2;
    
    return 0;
}

int runBasicTreeInterpreter(BTProgram *program, char *input, int inputLen){
    
    double x = *(double*)input;
    program->index = 0;
    program->isDead = false;
    
    double res = evaluate(program, x);
    program->generic.outputLen = 1;
    *(double*)program->generic.output = res;
    
    if(program->isDead) return -1;
    
    return 0;
}
