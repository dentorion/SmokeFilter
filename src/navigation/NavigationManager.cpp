#include "NavigationManager.h"

void NavigationManager::next(DeviceState& state)
{
    switch (state.uiMode)
    {
        case UiMode::MainMenu:

            nextMainMenu(state);

            break;

        case UiMode::Statistics:

            nextStatisticsPage(state);

            break;

        case UiMode::Settings:

            break;
    }
}

void NavigationManager::action(DeviceState& state)
{
    switch (state.uiMode)
    {
        case UiMode::MainMenu:

            enterCurrentScreen(state);

            break;

        case UiMode::Statistics:

            exitCurrentMode(state);

            break;

        case UiMode::Settings:

            exitCurrentMode(state);

            break;
    }
}

void NavigationManager::nextMainMenu(DeviceState& state)
{
    switch (state.currentScreen)
    {
        case ScreenType::Light:

            state.currentScreen =
                ScreenType::Fan;

            break;

        case ScreenType::Fan:

            state.currentScreen =
                ScreenType::Statistics;

            break;

        case ScreenType::Statistics:

            state.currentScreen =
                ScreenType::Light;

            break;
    }
}

void NavigationManager::nextStatisticsPage(
    DeviceState& state)
{
    state.statisticsPage++;

    if (state.statisticsPage > 1)
    {
        state.statisticsPage = 0;
    }
}

void NavigationManager::enterCurrentScreen(
    DeviceState& state)
{
    switch (state.currentScreen)
    {
        case ScreenType::Light:

            state.light.enabled =
                !state.light.enabled;

            break;

        case ScreenType::Fan:

            state.fan.enabled =
                !state.fan.enabled;

            break;

        case ScreenType::Statistics:

            state.statisticsPage = 0;

            state.uiMode =
                UiMode::Statistics;

            break;
    }
}

void NavigationManager::exitCurrentMode(
    DeviceState& state)
{
    state.statisticsPage = 0;

    state.uiMode =
        UiMode::MainMenu;
}