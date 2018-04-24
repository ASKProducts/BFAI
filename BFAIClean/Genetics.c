//
//  Genetics.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/22/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "Genetics.h"

extern Interpreter interpreter;

void processGenome(Genome *g){
    interpreter.process(g->dna, &g->program);
}
