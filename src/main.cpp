#include <iostream>

#include"SensorManager/SensorManager.h"

int main(){
    //SENSOR MANAGER: INIT AND START
    SensorManager sensorManager;
    if (!sensorManager.loadConfig("config/sensors/euroc.yaml")) return -1;
    if(!sensorManager.init()) return -1;
    if(!sensorManager.start()) return -1;

    //SLAM

    //STOP THE SENSOR MANAGER
    sensorManager.stop();
    return 0;
}