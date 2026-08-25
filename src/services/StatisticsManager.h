#pragma once

#include <stdint.h>

class TimeManager;

class StatisticsManager
{
public:
    void begin(
        TimeManager& timeManager
    );

    void update(
        bool lightEnabled,
        bool fanEnabled
    );

private:
    void recordLightState(
        bool enabled
    );

    void recordFanState(
        bool enabled
    );

private:
    TimeManager* _timeManager = nullptr;

    bool _previousLightEnabled = false;
    bool _previousFanEnabled = false;
};