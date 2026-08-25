#pragma once

#include "../state/DeviceState.h"

class NavigationManager
{
public:
    void next(DeviceState& state);

    void action(DeviceState& state);

private:
    void nextMainMenu(DeviceState& state);

    void nextStatisticsPage(DeviceState& state);

    void enterCurrentScreen(DeviceState& state);

    void exitCurrentMode(DeviceState& state);
};