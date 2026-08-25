#include "StatisticsManager.h"

#include "TimeManager.h"

#include "../database/Database.h"
#include "../models/Statistics.h"

void StatisticsManager::begin(
    TimeManager& timeManager
)
{
    _timeManager = &timeManager;

    _previousLightEnabled = false;
    _previousFanEnabled = false;
}

void StatisticsManager::update(
    bool lightEnabled,
    bool fanEnabled
)
{
    if (_timeManager == nullptr)
    {
        return;
    }

    if (lightEnabled != _previousLightEnabled)
    {
        recordLightState(
            lightEnabled
        );

        _previousLightEnabled =
            lightEnabled;
    }

    if (fanEnabled != _previousFanEnabled)
    {
        recordFanState(
            fanEnabled
        );

        _previousFanEnabled =
            fanEnabled;
    }
}

void StatisticsManager::recordLightState(
    bool enabled
)
{
    Statistics record;

    record.timestamp =
        _timeManager->now();

    record.type =
        StatisticsType::Light;

    record.state =
        enabled
            ? StatisticsEventState::On
            : StatisticsEventState::Off;

    record.synced = false;

    uint32_t id = 0;

    Database::statistics().insert(
        record,
        id
    );
}

void StatisticsManager::recordFanState(
    bool enabled
)
{
    Statistics record;

    record.timestamp =
        _timeManager->now();

    record.type =
        StatisticsType::Fan;

    record.state =
        enabled
            ? StatisticsEventState::On
            : StatisticsEventState::Off;

    record.synced = false;

    uint32_t id = 0;

    Database::statistics().insert(
        record,
        id
    );
}