//
//  FastBFInterpreter.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/20/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "DoubleBFInterpreter.h"
#include <assert.h>
#include <string.h>

extern Interpreter interpreters[];
extern Interpreter interpreter;
extern int numInterpreters;

int invs[DBF_MEM_MAX];

int modInverse(int a, int m){
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1){
        // q is quotient
        int q = a / m;
        int t = m;
        // m is remainder now, process same as
        // Euclid's algo
        m = a % m; a = t;
        t = y;
        // Update y and x
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    
    return x;
}

void initDoubleBFInterpreter(void){
    interpreters[numInterpreters].name = "FastBF";
    interpreters[numInterpreters].process = (ProcessFunc)processDoubleBFInterpreter;
    interpreters[numInterpreters].run = (RunFunc)runDoubleBFInterpreter;
    interpreters[numInterpreters].scan = scanDoubleBFInterpreter;
    interpreters[numInterpreters].save = saveDoubleBFInterpreter;
    interpreters[numInterpreters].validChars = "+-><[].,";
    interpreters[numInterpreters].AIChars = "+-><[].,";
    numInterpreters++;

    for (int i = 0; i < DBF_MEM_MAX; i++) {
        if(i % 2 == 1)
            invs[i] = modInverse(i, DBF_MEM_MAX);
    }
    
    assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING >= sizeof(DBFProgram));
}
void scanDoubleBFInterpreter(FILE *file){
    fscanf(file, "Tape Length: %d\n", &interpreter.tapeLength);
    char a;
    fscanf(file, "Allow Input: %c\n", &a);
    if(a == 'y')
        interpreter.validChars = "+-><[].,";
    else
        interpreter.validChars = "+-><[].";
    
    char possibleGenes[1000];
    fscanf(file, "Possible Genes: %s\n", possibleGenes);
    interpreter.AIChars = strdup(possibleGenes);
    
    fscanf(file, "Max Instruction Count: %d\n", &interpreter.maxInsCount);
    
}
void saveDoubleBFInterpreter(FILE *file){
    fprintf(file, "Tape Length: %d\n", interpreter.tapeLength);
    fprintf(file, "Allow Input: %c\n", interpreter.isValid[','] ? 'y' : 'n');
    fprintf(file, "Possible Genes: %s\n", interpreter.AIChars);
    fprintf(file, "Max Instruction Count: %d\n", interpreter.maxInsCount);
}

#define advance(code) do{code++;}while(*code && !interpreter.isValid[*code])
void processDoubleBFInterpreter(char *code, DBFProgram *program){

	processFastBFInterpreter(code, &program->program1);
	processFastBFInterpreter(code+150, &program->program2);
    //int len = (int)strlen(code);
/*    program->generic.code = code;
    int opC = 0;
    
    int openStack[MAX_FBF_OPS];
    int openStackSize = 0;
    
    bool isBalanced = true;
    int netShift = 0;
    int curInc = 0;
    
    while (*code && opC < MAX_FBF_OPS) {
        char c = *code;
        switch (c) {
            case '+':
            case '-':
                program->ops[opC].c = '+';
                int inc = 0;
                while (*code) {
                    if(*code == '+')inc++;
                    else if(*code == '-')inc--;
                    else break;
                    advance(code);
                }
                program->ops[opC].val = inc;
                if(netShift == 0) curInc += inc;
                if(inc != 0) opC++;
                break;
                
            case '>':
            case '<':
                program->ops[opC].c = '>';
                int shift = 0;
                while (*code) {
                    if(*code == '>')shift++;
                    else if(*code == '<')shift--;
                    else break;
                    advance(code);
                }
                program->ops[opC].val = shift;
                netShift += shift;
                if(shift != 0) opC++;
                break;
                
            case '.':
            case ',':
                program->ops[opC].c = c;
                opC++;
                isBalanced = false;
                advance(code);
                break;
                
            case '[':
                if(opC == 0 || program->ops[opC-1].c == ']'){
                    int open = 0;
                    do{
                        if(*code == '[') open++;
                        if(*code == ']') open--;
                        code++;
                    }while(*code && open > 0);
                }
                else{
                    openStack[openStackSize++] = opC;
                    isBalanced = true;
                    netShift = 0;
                    curInc = 0;
                    program->ops[opC].c = '[';
                    program->ops[opC].val = -1;
                    program->ops[opC].isBalanced = false;
                    opC++;
                    advance(code);
                }
                break;
                
            case ']':
                if(openStackSize == 0)goto bigbreak;
                program->ops[opC].c = ']';
                int openIndex = openStack[--openStackSize];
                program->ops[openIndex].val = opC;
                program->ops[opC].val = openIndex;
                if(isBalanced && netShift == 0){
                    program->ops[openIndex].isBalanced = true;
                    program->ops[openIndex].curInc = curInc;
                }
                isBalanced = false;
                opC++;
                advance(code);
                break;
                
            default:
                advance(code);
                break;
        }
    }
    
bigbreak:
    
    program->opCount = opC;
*/    
}


int runFastBFInterpreter(FBFProgram *program, char *input, int inputLen){
    
    int tapeLen = interpreter.tapeLength;
    unsigned char tape[tapeLen];
    int tapeIndex = 0;
    int farthestRight = 0;
    //Instead of always clearing the entire tape, we will only clear new blocks when we reach them.
    tape[0] = 0;
    program->generic.outputLen = 0;
    int insCount = 0;
    int maxInsCount = interpreter.maxInsCount;
    
    for (int i = 0; i < program->opCount && insCount < maxInsCount; i++, insCount++) {
        FBFOp op = program->ops[i];
        switch (op.c) {
            case '+':
                tape[tapeIndex] += op.val;
                break;
                
            case '>':
                tapeIndex += op.val;
                if(tapeIndex < 0 || tapeIndex >= tapeLen) goto superbreak;
                if(tapeIndex > farthestRight){
                    for (int j = farthestRight + 1; j <= tapeIndex; j++) {
                        tape[j] = 0;
                    }
                    farthestRight = tapeIndex;
                }
                break;
                
            case '.':
                if(program->generic.outputLen == PROGRAM_MAX_OUTPUT_LEN - 1) goto superbreak;
                program->generic.output[program->generic.outputLen++] = tape[tapeIndex];
                break;
                
            case ',':
                if(inputLen == 0)
                    tape[tapeIndex] = 0;
                else{
                    tape[tapeIndex] = *(input++);
                    inputLen--;
                }
                break;
                
            case '[':
                if(op.val == -1) goto superbreak;
                if(tape[tapeIndex] == 0){
                    i = op.val;
                }
                else{
                    if(op.isBalanced){
                        //balanced loop. if 256 and the amount which the current block changes aren't
                        //relatively prime, then its an infinite loop. Otherwise the whole program repeats -kn^(-1) (mod M) times
                        //where k is the value of the current block, n is the amount it updates, and M is 256. Being relatively prime
                        //to 256 is the same as being odd, so we utilize this here
                        
                        if(op.curInc % 2 == 0)
                            goto superbreak;
                        
                        int n = (unsigned char)op.curInc;
                        int inv = invs[n];
                        int l = (unsigned char)(- tape[tapeIndex] * inv);
                        
                        i++;
                        while(i < program->opCount){
                            FBFOp next = program->ops[i];
                            if(next.c == ']') break;
                            if(next.c == '>') {
                                tapeIndex += next.val;
                                if(tapeIndex < 0 || tapeIndex > tapeLen) goto superbreak;
                                if(tapeIndex > farthestRight){
                                    for (int j = farthestRight + 1; j <= tapeIndex; j++) {
                                        tape[j] = 0;
                                    }
                                    farthestRight = tapeIndex;
                                }
                            }
                            if(next.c == '+'){
                                tape[tapeIndex] += l*next.val;
                            }
                            i++;
                        }
                        
                    }
                }
                break;
                
            case ']':
                if(tape[tapeIndex] != 0){
                    i = op.val;
                }
                break;
                
            default:
                break;
        }
    }
    
superbreak:
    program->generic.output[program->generic.outputLen] = 0;
    return insCount;
    
}










