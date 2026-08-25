#include "IconWidget.h"

#include "../display/DisplayRenderer.h"

void IconWidget::draw(DisplayRenderer& renderer, const Icon& icon)
{
    auto& lcd = renderer.lcd();

    constexpr int iconOffsetY = -10;

    const int x = (lcd.width()  - icon.width)  / 2;
    const int y = (lcd.height() - icon.height) / 2 + iconOffsetY;

    lcd.pushImage(
        x,
        y,
        icon.width,
        icon.height,
        icon.pixels
    );
}