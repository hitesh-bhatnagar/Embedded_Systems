#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "logger.h"

void log_data(int value){
    FILE *logfile;

    logfile = fopen("sensor_log.txt", "a");     // append mode

    if(logfile == NULL){
        printf("Error opening log file:\n");
        return;

    }

    fprintf(logfile, "Sensor Reading : %d\n", value);
    fclose(logfile);
}