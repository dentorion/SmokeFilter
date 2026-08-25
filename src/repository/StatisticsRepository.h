#pragma once

#include <stdint.h>

#include "../models/StatisticsScreenData.h"

class StatisticsRepository
{
public:
    static constexpr uint8_t MaxEvents = 4;

    bool loadRecentEvents(
        StatisticsEventView (&events)[MaxEvents],
        uint8_t& eventCount
    );

private:
    void mapEvent(
        const Statistics& statistics,
        StatisticsEventView& event
    );

    void formatTime(
        uint32_t timestamp,
        char* buffer
    );
};