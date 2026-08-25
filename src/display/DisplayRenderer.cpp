#include "DisplayRenderer.h"

bool DisplayRenderer::begin()
{
    _lcd.init();

    _lcd.setRotation(0);

    _lcd.fillScreen(TFT_BLACK);

    _lcd.setTextColor(TFT_WHITE);

    _lcd.setTextSize(1);

    _lcd.setTextDatum(MC_DATUM);

    return true;
}

void DisplayRenderer::clear()
{
    _lcd.fillScreen(TFT_BLACK);
}

void DisplayRenderer::update()
{
    // Зарезервировано для будущего использования.
}

void DisplayRenderer::drawCenteredText(const String& text)
{
    _lcd.drawString(
        text,
        _lcd.width() / 2,
        _lcd.height() / 2
    );
}

LGFX& DisplayRenderer::lcd()
{
    return _lcd;
}