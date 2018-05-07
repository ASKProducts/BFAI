//
//  FastBFInterpreter.h
//  BFAIClean
//
//

/* 	The basic concept here is that we can increase genetic diversity by
    having each program contain 2 different codes and its fitness be the
    fitness of a better one. 

	Breeding can be done by recombination between the two codes of each,
    and also whatever was being done before. 
 */

#ifndef DoubleBFInterpreter_h
#define DoubleBFInterpreter_h

#include "Interpreter.h"
#include "FastBFInterpreter.h"

#define MAX_DBF_OPS 500

//The fast-bf interpreter will make use of the fact that the memory max is explicitly 256. Other interpreters will be more versatile.
#define DBF_MEM_MAX 256
/*
typedef struct _DBFOp{
    char c;
    short val;
    
    bool isBalanced;
    short netShift;
    short curInc;
} DBFOp;
*/
typedef struct _DBFProgram{
	FBFProgram program1;
	FBFProgram program2;
} DBFProgram;


void initDoubleBFInterpreter(void);
void scanDoubleBFInterpreter(FILE *file);
void saveDoubleBFInterpreter(FILE *file);
void processDoubleBFInterpreter(char *code, DBFProgram *program);
int runDoubleBFInterpreter(DBFProgram *program, char *input, int inputLen);



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
