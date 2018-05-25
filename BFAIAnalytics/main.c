//
//  main.c
//  BFAIAnalytics
//
//  Created by Aaron Kaufer on 5/21/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include <stdio.h>

#include "includes.h"

extern GeneticAlgorithm algorithm;

char *loadfileName ="/Users/AKaufer/Documents/BFAIClean/BFAIAnalytics/AnalyticsSettings.lf";


int main(int argc, const char * argv[]) {
    srand((int)time(NULL));
    
    FILE *file = fopen(loadfileName, "r");
    
    initializeSettings(file);
    
    fscanf(file, "\n");
    
    char description[1000];
    fgets(description, 1000, file);
    
    int numTrials;
    fscanf(file, "Number of Trials: %d", &numTrials);
    
    double times[numTrials];
    double timesSum = 0;
    for (int i = 0; i < numTrials; i++) {
        clock_t startClock = clock();
        algorithm.run(file);
        clock_t endClock = clock();
        
        times[i] = (double)(endClock-startClock)/CLOCKS_PER_SEC;
        
        timesSum += times[i];
        printf("\n\nAverage Time Taken: %.2f\n\n", timesSum/(i+1));
    }
    
    saveSettings();
    
    fprintf(file, "\n%s", description);
    fprintf(file, "Number of Trials: %d", numTrials);
    
    printf("Report:\n");
    printf("%s", description);
    printf("Number of Trials: %d\n", numTrials);
    printf("Times:\n");
    printf("{");
    for (int i = 0; i < numTrials; i++) {
        printf("%.2f%s", times[i], i < numTrials-1 ? ", " : "");
    }
    printf("}\n");
    printf("Average: %.2f\n", timesSum/numTrials);
    
    fclose(file);
    return 0;
}
