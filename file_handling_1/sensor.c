#include <stdlib.h>
#include "sensor.h"

#include <time.h>

int read_sensor(){
    srand(time(NULL));
    return rand() % 100; 
}
