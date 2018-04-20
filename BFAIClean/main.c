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

extern Interpreter interpreter;


/*
 Key components of genetic algorithm:
 
 breeding method
 mutation method
 breeding selection method
 overarching strategy
 */

int main(int argc, const char * argv[]) {
    FILE *file = fopen("./FastTest.lf", "rw");
    initializeSettings(file);
    
    Program p;
    
    
    printf("%s\n", p.generic.output);
    
    return 0;
}
