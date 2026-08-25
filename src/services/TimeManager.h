#pragma once

#include <stdint.h>

class TimeManager
{
public:
    void begin();

    uint32_t now() const;

    uint32_t elapsed(uint32_t startTime) const;
};