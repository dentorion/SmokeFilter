#include "ScreenManager.h"

#include "../display/DisplayManager.h"

void ScreenManager::begin(DisplayManager& displayManager)
{
    _displayManager = &displayManager;
}

void ScreenManager::showLight(const LightScreenData& data)
{
    _lightScreen.setData(data);
    _displayManager->show(_lightScreen);
}

void ScreenManager::showFan(const FanScreenData& data)
{
    _fanScreen.setData(data);
    _displayManager->show(_fanScreen);
}

void ScreenManager::showStatistics(const StatisticsScreenData& data)
{
    _statisticsScreen.setData(data);
    _displayManager->show(_statisticsScreen);
}