//
//  Timer.h
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include <stdio.h>

#include <time.h>


typedef struct _Timer{
    clock_t startClock;
    clock_t lastUpdate;
    
    double totalTime; //in seconds
    double timeSinceLastUpdate;
}Timer;

Timer newTimer(double intialOffset);

//updates the timer, returns the time in seconds since last update.
void updateTimer(Timer *timer);

#endif /* Timer_h */
