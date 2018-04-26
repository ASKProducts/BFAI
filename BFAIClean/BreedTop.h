//
//  BreedTop.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/24/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef BreedTop_h
#define BreedTop_h

#include <stdio.h>
#include "BreedingSelector.h"
/* Selection algorithm which selects one parent to be from the top elitePercent and the other to be a commonner */

void initBreedTop(void);
void breedTopPrep(Population *p);
Parents breedTopSelect(Population *p, int childNum);
void scanBreedTop(FILE *file);
void saveBreedTop(FILE *file);

 

#endif /* BreedTop_h */
