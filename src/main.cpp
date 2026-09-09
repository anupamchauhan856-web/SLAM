#include <iostream>
#include<thread>
#include<chrono>

#include"SensorManager/SensorManager.h"

int main(){
    //SENSOR MANAGER: INIT AND START
    SensorManager sensorManager;
    if (!sensorManager.loadConfig("config/sensors/euroc.yaml")) return -1;
    if(!sensorManager.init()) return -1;
    if(!sensorManager.start()) return -1;

    //PAUSE FOR SOME TIME TO GET THE DATA
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //READ SENSOR DATA
    SensorManager::Data data;
    while (sensorManager.popNext(data))
    {
        std::visit(
            [](const auto& sensorData)
            {
                std::cout
                    << "Sensor: " << sensorData.sensor_id
                    << " | Timestamp: " << sensorData.timestamp
                    << '\n';
            },
            data);
    }


    //SLAM

    //STOP THE SENSOR MANAGER
    sensorManager.stop();
    return 0;
}