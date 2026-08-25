#include "StateWidget.h"

#include "../display/DisplayRenderer.h"

void StateWidget::draw(
    DisplayRenderer& renderer,
    const char* text)
{
    auto& lcd = renderer.lcd();

    lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    lcd.setTextSize(2);
    lcd.setTextDatum(MC_DATUM);

    lcd.drawString(
        text,
        lcd.width() / 2,
        215
    );
}