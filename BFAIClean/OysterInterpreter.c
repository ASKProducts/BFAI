//
//  OysterInterpreter.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/28/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "OysterInterpreter.h"
#include <string.h>

extern Interpreter interpreters[];
extern Interpreter interpreter;
extern int numInterpreters;

void initOysterInterpreter(void){
    interpreters[numInterpreters] = (Interpreter){
        .name = "Oyster",
        .scan = scanOysterInterpreter,
        .save = saveOysterInterpreter,
        .process = (ProcessFunc)processOysterInterpreter,
        .run = (RunFunc)runOysterInterpreter
    };
    numInterpreters++;
    
}
void scanOysterInterpreter(FILE *file){
    fscanf(file, "Number of Lines: %d\n", &interpreter.numLines);
    fscanf(file, "Line Length: %d\n", &interpreter.lineLength);
    
    char a;
    fscanf(file, "Continue Lines: %c\n", &a);
    interpreter.continueLines = (a == 'y');
    
    fscanf(file, "Tape Length: %d\n", &interpreter.tapeLength);
    fscanf(file, "Max Instruction Count: %d\n", &interpreter.maxInsCount);
    
    interpreter.validChars = "+-,.><ABDEFGHIJKLMNOPQRSTUVWXYZ";
    interpreter.AIChars = strdup(interpreter.validChars);
    interpreter.AIChars[6 + interpreter.numLines-1] = 0;
}
void saveOysterInterpreter(FILE *file){
    fprintf(file, "Number of Lines: %d\n", interpreter.numLines);
    fprintf(file, "Line Length: %d\n", interpreter.lineLength);
    fprintf(file, "Continue Lines: %c\n", interpreter.continueLines ? 'y' : 'n');
    fprintf(file, "Tape Length: %d\n", interpreter.tapeLength);
    fprintf(file, "Max Instruction Count: %d\n", interpreter.maxInsCount);
}
void processOysterInterpreter(char *code, OysterProgram *program){
    program->generic.code = code;
    for (int i = 0; i < interpreter.numLines; i++) {
        program->lines[i] = code + i * interpreter.lineLength;
    }
}
int runOysterInterpreter(OysterProgram *program, char *input, int inputLen){
    
    int currentLine = 0;
    int currentOp = 0;
    
    char tape[interpreter.tapeLength];
    memset(tape, 0, interpreter.tapeLength);
    int loc = 0;
    
    program->generic.outputLen = 0;
    
    int insCount = 0;
    
    while (currentOp < interpreter.lineLength && insCount < interpreter.maxInsCount) {
        char c = program->lines[currentLine][currentOp];
        switch (c) {
            case '+':
                tape[loc]++;
                break;
            case '-':
                tape[loc]--;
                break;
            case '*':
                tape[loc] += 16;
                break;
            case ',':
                if(inputLen){
                    tape[loc] = *input;
                    input++;
                    inputLen--;
                }
                else tape[loc] = 0;
                break;
            case '.':
                if(program->generic.outputLen == PROGRAM_MAX_OUTPUT_LEN - 1) goto superbreak;
                program->generic.output[program->generic.outputLen++] = tape[loc];
                break;
            case '>':
                loc++;
                if(loc >= interpreter.tapeLength) goto superbreak;
                break;
            case '<':
                loc --;
                if(loc < 0) goto superbreak;
                break;
                
            default:
                break;
        }
        if(c >= 'A' && c <= 'Z' && tape[loc] != 0){
            currentLine = c - 'A';
            currentOp = 0;
        }
        else{
            currentOp++;
            if(interpreter.continueLines){
                if(currentOp == interpreter.lineLength){
                    currentLine++;
                    currentOp = 0;
                    if(currentLine == interpreter.numLines)break;
                }
            }
        }
        insCount++;
    }
    
superbreak:
    program->generic.output[program->generic.outputLen] = 0;
    return insCount;
}







