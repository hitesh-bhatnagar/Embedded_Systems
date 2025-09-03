#include <stdio.h>
#include "sensor.h"
#include "logger.h"

int main(void){
    for(int i = 0; i < 10 ; i++){
        int value = read_sensor();
        printf("Sensor reading %d: %d\n", i+1, value);
        log_data(value);
    }
    return 0;   
}