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

/******** GLOBAL SETTINGS ********/
//These are the settings that need to be hardcoded into C instead of read from the loadfile
#define PROGRAM_MAX_OUTPUT_LEN 100

/******** INTERPRETER-SPECIFIC SETTINGS *******/

//To add a new interpreter to the list, just add its init func to this list
#define initFuncs {initStupidInterpreter, initFastBFInterpreter}

//For faster results, if you know what program type you're using, you can set GENERIC_PROGRAM_PADDING to (sizeof(YOUR_PROGRAM_TYPE) - sizeof(GenericProgram)), or just hardcode smaller values
#define GENERIC_PROGRAM_PADDING 10100


#endif /* Settings_h */
