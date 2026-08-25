#include "LightScreen.h"

#include "../display/DisplayRenderer.h"
#include "../widgets/IconWidget.h"
#include "../widgets/StateWidget.h"
#include "../widgets/StatusBarWidget.h"
#include "../widgets/TitleWidget.h"

namespace
{
    IconWidget iconWidget;
    StatusBarWidget statusBarWidget;
    TitleWidget titleWidget;
    StateWidget stateWidget;
}

void LightScreen::setData(const LightScreenData& data)
{
    _data = data;
}

void LightScreen::draw(DisplayRenderer& renderer)
{
    renderer.clear();

    statusBarWidget.draw(
        renderer,
        _data.led1,
        _data.led2,
        _data.led3,
        _data.led4
    );

    iconWidget.draw(
        renderer,
        _data.enabled
            ? _data.iconOn
            : _data.iconOff
    );

    titleWidget.draw(
        renderer,
        _data.title
    );

    stateWidget.draw(
        renderer,
        _data.state
    );

    renderer.update();
}