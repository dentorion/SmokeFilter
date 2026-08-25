#pragma once

#include <stdint.h>

enum class StatisticsType : uint8_t
{
    Light = 0,
    Fan = 1
};

enum class StatisticsEventState : uint8_t
{
    Off = 0,
    On = 1
};

struct Statistics
{
    uint32_t timestamp = 0;

    StatisticsType type =
        StatisticsType::Light;

    StatisticsEventState state =
        StatisticsEventState::Off;

    bool synced = false;
};