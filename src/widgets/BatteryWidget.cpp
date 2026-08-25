#include "BatteryWidget.h"

#include "../display/DisplayRenderer.h"

void BatteryWidget::draw(DisplayRenderer& renderer, uint8_t batteryPercent)
{
    auto& lcd = renderer.lcd();

    constexpr int radius = 5;
    constexpr int spacing = 8;

    const int totalWidth = radius * 2 * 4 + spacing * 3;
    const int startX = (lcd.width() - totalWidth) / 2;
    const int y = 18;

    uint8_t level = 0;

    if (batteryPercent >= 75)
        level = 4;
    else if (batteryPercent >= 50)
        level = 3;
    else if (batteryPercent >= 25)
        level = 2;
    else if (batteryPercent > 0)
        level = 1;

    for (uint8_t i = 0; i < 4; ++i)
    {
        uint16_t color = (i < level)
            ? TFT_GREEN
            : TFT_RED;

        lcd.fillCircle(
            startX + radius + i * (radius * 2 + spacing),
            y,
            radius,
            color
        );
    }
}