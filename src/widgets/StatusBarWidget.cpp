#include "StatusBarWidget.h"

#include "../display/DisplayRenderer.h"

void StatusBarWidget::draw(
    DisplayRenderer& renderer,
    bool led1,
    bool led2,
    bool led3,
    bool led4)
{
    auto& lcd = renderer.lcd();

    constexpr int radius = 6;
    constexpr int y = 16;
    constexpr int spacing = 24;
    constexpr int startX = 84;

    const uint16_t green = TFT_GREEN;
    const uint16_t red = TFT_RED;

    lcd.fillCircle(startX + spacing * 0, y, radius, led1 ? green : red);
    lcd.fillCircle(startX + spacing * 1, y, radius, led2 ? green : red);
    lcd.fillCircle(startX + spacing * 2, y, radius, led3 ? green : red);
    lcd.fillCircle(startX + spacing * 3, y, radius, led4 ? green : red);
}