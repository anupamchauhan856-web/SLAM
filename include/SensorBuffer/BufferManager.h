//THIS CLASS WILL HOLD BUFFERS OF ALL SENSORS
//WILL BE OWNED BY SENSOR MANAGER
//SENSOR MANAGER WILL FETCH SENSOR BUFFERS BASED ON SENSOR IDs
//WILL DELIVER SENSOR DATA CHRONOLOGICALLY BASED ON TIMESTAMP
//WILL ENABLE BUFFERS ONLY FOR THE SENSORS BEING USED

#pragma once

#include <cstdint>
#include <map>
#include <mutex>
#include <memory>
#include <variant>

#include"CameraData.h"
#include"ImuData.h"

class BufferManager{
public:
    //DATA SHOULD BE ABLE TO HOLD OBJECTS OF MORE THAN ONE TYPES
    using Data=std::variant<CameraData,ImuData>;

    //CHRONOLOGICAL PUBLISHING OF SENSOR DATA
    bool push(Data data);
    bool popNext(Data& data);

    //GET DATA: READ ONLY USING CONST
    bool empty() const;
    size_t size() const;

private:
    //PREVENT RACE CONDITION OF BUFFER WRITE AND READ
    mutable std::mutex mutex_;
    std::multimap<int64_t, Data> buffer_;
};