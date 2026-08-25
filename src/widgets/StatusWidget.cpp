#include "StatusWidget.h"

#include "../display/DisplayRenderer.h"

void StatusWidget::draw(DisplayRenderer& renderer, bool enabled)
{
    auto& lcd = renderer.lcd();

    lcd.setTextDatum(MC_DATUM);
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextSize(2);

    lcd.drawString(
        enabled ? "ON" : "OFF",
        lcd.width() / 2,
        lcd.height() - 28
    );
}