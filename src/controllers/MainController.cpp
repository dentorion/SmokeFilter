#include "MainController.h"

#include "../resources/Icons.h"

void MainController::begin()
{
    displayManager.begin();

    screenManager.begin(displayManager);

    wifiManager.begin();

    settingsManager.begin();

    buttonManager.begin();

    sensorManager.begin();

    hardwareManager.begin();

    timeManager.begin();

    statisticsManager.begin(
        timeManager
    );

    state.light.enabled = false;

    state.fan.enabled = false;
    state.fan.speed = 0;

    state.battery.percent = 100;

    state.wifi.connected = false;

    state.sensors.temperature =
        sensorManager.temperature();

    state.sensors.humidity =
        sensorManager.humidity();

    state.sensors.airQuality =
        sensorManager.airQuality();

    state.currentScreen =
        ScreenType::Light;

    state.uiMode =
        UiMode::MainMenu;

    state.statisticsPage = 0;

    _testTimer =
        timeManager.now();

    _testStep = 0;

    showCurrentScreen();
}

void MainController::update()
{
    buttonManager.update();

    wifiManager.update();

    sensorManager.update();

    hardwareManager.update();

    statisticsManager.update(
        state.light.enabled,
        state.fan.enabled
    );

    updateInputs();

    updateLogic();

    updateTestMode();

    updateOutputs();

    updateDisplay();
}

void MainController::updateInputs()
{
}

void MainController::updateLogic()
{
    state.wifi.connected =
        wifiManager.isConnected();

    state.sensors.temperature =
        sensorManager.temperature();

    state.sensors.humidity =
        sensorManager.humidity();

    state.sensors.airQuality =
        sensorManager.airQuality();

    if (buttonManager.isNextPressed())
    {
        navigationManager.next(state);

        showCurrentScreen();
    }

    if (buttonManager.isActionPressed())
    {
        navigationManager.action(state);

        showCurrentScreen();
    }
}

void MainController::updateTestMode()
{
    if (!_testMode)
    {
        return;
    }

    const uint32_t now =
        timeManager.now();

    if (now - _testTimer < 3000)
    {
        return;
    }

    _testTimer = now;

    switch (_testStep)
    {
        case 0:
        {
            state.currentScreen =
                ScreenType::Fan;

            state.uiMode =
                UiMode::MainMenu;

            state.statisticsPage = 0;

            showCurrentScreen();

            _testStep++;

            break;
        }

        case 1:
        {
            state.currentScreen =
                ScreenType::Statistics;

            state.uiMode =
                UiMode::MainMenu;

            state.statisticsPage = 0;

            showCurrentScreen();

            _testStep++;

            break;
        }

        case 2:
        {
            navigationManager.action(state);

            showCurrentScreen();

            _testStep++;

            break;
        }

        case 3:
        {
            navigationManager.next(state);

            showCurrentScreen();

            _testStep++;

            break;
        }

        case 4:
        {
            navigationManager.action(state);

            showCurrentScreen();

            _testStep++;

            break;
        }

        default:
        {
            break;
        }
    }
}

void MainController::updateOutputs()
{
    hardwareManager.setLight(
        state.light.enabled
    );

    hardwareManager.setFan(
        state.fan.enabled,
        state.fan.speed
    );
}

void MainController::updateDisplay()
{
}

void MainController::showCurrentScreen()
{
    switch (state.currentScreen)
    {
        case ScreenType::Light:
        {
            LightScreenData data;

            data.enabled =
                state.light.enabled;

            data.batteryPercent =
                state.battery.percent;

            data.led1 = true;
            data.led2 = true;
            data.led3 = true;
            data.led4 = true;

            data.title =
                "LIGHT";

            data.state =
                state.light.enabled
                    ? "ON"
                    : "OFF";

            data.iconOff =
                ICON_LIGHT_OFF;

            data.iconOn =
                ICON_LIGHT_ON;

            screenManager.showLight(data);

            break;
        }

        case ScreenType::Fan:
        {
            FanScreenData data;

            data.enabled =
                state.fan.enabled;

            data.batteryPercent =
                state.battery.percent;

            data.led1 = true;
            data.led2 = true;
            data.led3 = true;
            data.led4 = true;

            data.title =
                "FAN";

            data.state =
                state.fan.enabled
                    ? "ON"
                    : "OFF";

            data.iconOff =
                ICON_FAN_OFF;

            data.iconOn =
                ICON_FAN_ON;

            screenManager.showFan(data);

            break;
        }

        case ScreenType::Statistics:
        {
            StatisticsScreenData data;

            data.page =
                state.statisticsPage;

            data.showData =
                (state.uiMode ==
                 UiMode::Statistics);

            data.temperature =
                state.sensors.temperature;

            data.humidity =
                state.sensors.humidity;

            data.airQuality =
                state.sensors.airQuality;

            data.batteryPercent =
                state.battery.percent;

            data.eventCount = 0;

            if (data.showData &&
                data.page == 1)
            {
                statisticsRepository.loadRecentEvents(
                    data.events,
                    data.eventCount
                );
            }

            data.led1 = true;
            data.led2 = true;
            data.led3 = true;
            data.led4 = true;

            data.title =
                "STATS";

            screenManager.showStatistics(data);

            break;
        }
    }
}