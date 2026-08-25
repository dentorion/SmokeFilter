#include "TimeManager.h"

#include <Arduino.h>

void TimeManager::begin()
{
}

uint32_t TimeManager::now() const
{
    return millis();
}

uint32_t TimeManager::elapsed(
    uint32_t startTime
) const
{
    return millis() - startTime;
}