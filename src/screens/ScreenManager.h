#pragma once

#include "LightScreen.h"
#include "FanScreen.h"
#include "StatisticsScreen.h"

class DisplayManager;

class ScreenManager
{
public:
    void begin(DisplayManager& displayManager);

    void showLight(const LightScreenData& data);
    void showFan(const FanScreenData& data);
    void showStatistics(const StatisticsScreenData& data);

private:
    DisplayManager* _displayManager = nullptr;

    LightScreen _lightScreen;
    FanScreen _fanScreen;
    StatisticsScreen _statisticsScreen;
};