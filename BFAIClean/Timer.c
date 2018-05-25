//
//  Timer.c
//  BFAIClean
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include "Timer.h"
#include <time.h>


Timer newTimer(double initialOffset){
    Timer newTimer;
    clock_t cl = clock();
    newTimer.lastUpdate = cl;
    newTimer.startClock = cl;
    
    newTimer.timeSinceLastUpdate = 0;
    newTimer.totalTime = initialOffset;
    
    return newTimer;
}

#define NOTICEABLE_DIFFERENCE 0.0001

//updates the timer, returns the time in seconds since last update.
void updateTimer(Timer *timer){
    clock_t cl = clock();
    
    double timeSinceLast = (double)(cl - timer->lastUpdate)/CLOCKS_PER_SEC;
    
    if(timeSinceLast >= NOTICEABLE_DIFFERENCE){
        timer->lastUpdate = cl;
        timer->timeSinceLastUpdate = timeSinceLast;
        timer->totalTime += timeSinceLast;
    }
}
