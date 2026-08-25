#pragma once

#include "../display/DisplayManager.h"
#include "../hardware/HardwareManager.h"
#include "../input/ButtonManager.h"
#include "../navigation/NavigationManager.h"
#include "../network/WiFiManager.h"
#include "../repository/StatisticsRepository.h"
#include "../screens/ScreenManager.h"
#include "../sensors/SensorManager.h"
#include "../services/SettingsManager.h"
#include "../services/StatisticsManager.h"
#include "../services/TimeManager.h"
#include "../state/DeviceState.h"

class MainController
{
public:
    void begin();

    void update();

private:
    void updateInputs();
    void updateLogic();
    void updateOutputs();
    void updateDisplay();

    void updateTestMode();

    void showCurrentScreen();

private:
    DeviceState state;

    DisplayManager displayManager;

    ScreenManager screenManager;

    NavigationManager navigationManager;

    WiFiManager wifiManager;

    SettingsManager settingsManager;

    ButtonManager buttonManager;

    SensorManager sensorManager;

    HardwareManager hardwareManager;

    TimeManager timeManager;

    StatisticsManager statisticsManager;

    StatisticsRepository statisticsRepository;

    bool _testMode = false;

    uint32_t _testTimer = 0;

    uint8_t _testStep = 0;
};