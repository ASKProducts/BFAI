//
//  main.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include <stdio.h>
#include "Settings.h"
#include "Interpreter.h"
#include "StupidInterpreter.h"
#include "FastBFInterpreter.h"
#include "Algorithm.h"

extern Interpreter interpreter;


/*
 Key components of genetic algorithm:
 
 interpreter
 breeding method
 mutation method
 breeding selection method
 fitness function
 overarching strategy
 */

int main(int argc, const char * argv[]) {
    FILE *file = fopen("./FastTest.lf", "rw");
    initializeSettings(file);
    
    Program p;
    interpreter.process(",[.,]", &p);
    interpreter.run(&p, "Hello World!", 12);
    
    printf("%s\n", p.generic.output);
    
    return 0;
}
