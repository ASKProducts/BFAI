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
        .run = (RunFunc)runBasicTreeInterpreter,
        .print = (PrintFunc)printTreeExpression
    };
    
    assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING >= sizeof(BTProgram));
    
    for (int i = 0; i < 9; i++) {
        arity['0' + i] = 0;
    }
    arity['p'] = 0; //pi
    arity['e'] = 0; //e
    arity['x'] = 0; //input variable x
    arity['k'] = 0; //instruction to kill the program
    
    arity['+'] = 2; // +
    arity['-'] = 2; // -
    arity['*'] = 2; // *
    arity['/'] = 2; // /
    arity['^'] = 2; // ^ (exponentation)
    
    arity['E'] = 1; // exp(X)
    arity['L'] = 1; // log(X)
    arity['I'] = 1; // 1/X
    arity['S'] = 1; // sin(X)
    arity['C'] = 1; // cos(X)
    arity['T'] = 1; // tan(X)
    arity['_'] = 1; // X (just the identity function)
}

void parse(char *str, int *i){
    char c = (*i < strlen(str)) ? str[*i] : '0';
    (*i)++;
    if (arity[c] == 2) {
        printf("(");
        parse(str, i);
        printf("%c", c);
        parse(str, i);
        printf(")");
    }
    else if (arity[c] == 1){
        if (c == 'E') printf("exp");
        else if (c == 'L') printf("log");
        else if (c == 'S') printf("sin");
        else if (c == 'C') printf("cos");
        else if (c == 'T') printf("tan");
        else if (c == 'I') printf("(1/");
        else if (c == '_') ;
        else printf("%c", c);
        printf("(");
        parse(str, i);
        printf(")");
        if(c == 'I') printf(")");
    }
    else if (arity[c] == 0){
        if(c == 'p') printf("pi");
        else printf("%c", c);
    }
}

void printTreeExpression(BTProgram *program){
    int i = 0;
    printf("\n%s\n\n", program->generic.code);
    parse(program->generic.code, &i);
    printf("\n");
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

double evaluate(BTProgram *program, double x, int *insCount){
    if(program->isDead || program->index >= program->len) return 0;
    
    char c = program->generic.code[program->index++];
    (*insCount)++;
    if (arity[c] == 0) {
        if(c >= '0' && c <= '9') return c - '0';
        if(c == 'p') return M_PI;
        if(c == 'e') return M_E;
        if(c == 'x') return x;
        if (c == 'k') {
            program->isDead = true;
            return 0;
        }
    }
    else if (arity[c] == 1){
        double val = evaluate(program, x, insCount);
        if (c == 'E')
            return exp(val);
        else if (c == 'L'){
            if (val <= 0){
                program->isDead = true;
                return 0;
            }
            return log(val);
        }
        else if (c == 'I'){
            if(val == 0){
                program->isDead = true;
                return 0;
            }
            return 1/val;
        }
        else if (c == 'S')
            return sin(val);
        else if (c == 'C')
            return cos(val);
        else if (c == 'T')
            return tan(val);
        else if (c == '_')
            return val;
    }
    else if (arity[c] == 2){
        double val1 = evaluate(program, x, insCount);
        double val2 = evaluate(program, x, insCount);
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
            if (val1 < 0) {
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
    
    int insCount= 0;
    double res = evaluate(program, x, &insCount);
    program->generic.outputLen = 1;
    *(double*)program->generic.output = res;
    
    if(program->isDead) return -1;
    
    return insCount;
}
