#pragma once

#include "Sensors/Buffers/BufferManager.h"

//ROLE: GIVE THE NEXT MEASUREMENT FROM A DATA SOURCE
class IDataSource
{
public:
    virtual ~IDataSource() = default;

    virtual bool init() = 0;

    // Produce the next measurement.
    virtual bool readNext(BufferManager::Data& data) = 0;

    // True when there are no more measurements.
    virtual bool isFinished() const = 0;
};