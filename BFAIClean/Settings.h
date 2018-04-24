//
//  Settings.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 4/17/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Settings_h
#define Settings_h

#include <stdio.h>

void initializeSettings(FILE *file);
void saveSettings(void);

//Each component has their own scan function. Scanning should scan into the universal global variables.
typedef void (*ScanFunc) (FILE *file);

//Saving should generally match scanning identically
typedef void (*SaveFunc) (FILE *file);

typedef void (*InitFunc) (void);

/******** GLOBAL SETTINGS ********/
//These are the settings that need to be hardcoded into C instead of read from the loadfile
#define PROGRAM_MAX_OUTPUT_LEN 100
#define MAX_DNA_LENGTH 1000

//For faster results(?), if you know what program type you're using, you can set GENERIC_PROGRAM_PADDING to (sizeof(YOUR_PROGRAM_TYPE) - sizeof(GenericProgram)), or just hardcode smaller values
#define GENERIC_PROGRAM_PADDING 5500

/******** STRUCTURE SETTINGS *******/

//To add a new interpreter to the list, just add its init func to this list
//Init functions do all their initializations into interpreters[numInterpreters], and at the end of
//the function must call numInterpreters++ and:
// assert(sizeof(GenericProgram) + GENERIC_PROGRAM_PADDING < sizeof( PROGRAM TYPE ));
#define interpreterInits {initStupidInterpreter, initFastBFInterpreter}

#define algorithmInits {initSinglePopulation}

#define breederInits {initRandomCrossover}

#define mutatorInits {initRandomReplace}



#endif /* Settings_h */
