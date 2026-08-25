#pragma once

#include <stdint.h>

#include "Statistics.h"

struct StatisticsEventView
{
    char time[9] = "00:00:00";

    StatisticsType type =
        StatisticsType::Light;

    StatisticsEventState state =
        StatisticsEventState::Off;

    bool synced = false;
};

struct StatisticsScreenData
{
    uint8_t page = 0;

    bool showData = false;

    // Текущие показатели датчиков
    float temperature = 0.0f;

    float humidity = 0.0f;

    uint16_t airQuality = 0;

    // Последние события из БД
    StatisticsEventView events[4];

    uint8_t eventCount = 0;

    // Батарея
    uint8_t batteryPercent = 100;

    // Индикаторы
    bool led1 = false;
    bool led2 = false;
    bool led3 = false;
    bool led4 = false;

    const char* title = "STATS";
};