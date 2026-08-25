#include "StatisticsScreen.h"

#include "../display/DisplayRenderer.h"
#include "../widgets/IconWidget.h"
#include "../widgets/TitleWidget.h"

namespace
{
    IconWidget iconWidget;
    TitleWidget titleWidget;
}

void StatisticsScreen::setData(
    const StatisticsScreenData& data
)
{
    _data = data;
}

void StatisticsScreen::draw(
    DisplayRenderer& renderer
)
{
    renderer.clear();

    /*
     * -------------------------------------------------
     * PREVIEW
     * -------------------------------------------------
     *
     * Обычный пункт главного меню.
     */
    if (!_data.showData)
    {
        iconWidget.draw(
            renderer,
            ICON_STATISTICS
        );

        titleWidget.draw(
            renderer,
            _data.title
        );

        renderer.update();

        return;
    }

    LGFX& lcd = renderer.lcd();

    lcd.setTextDatum(MC_DATUM);
    lcd.setTextColor(TFT_WHITE);

    /*
     * -------------------------------------------------
     * PAGE 0 — CURRENT SENSOR DATA
     * -------------------------------------------------
     *
     * 3 строки располагаются единым блоком
     * строго по центру экрана.
     *
     * Индикатор батареи не выводим.
     */
    if (_data.page == 0)
    {
        lcd.setFont(&fonts::Font0);
        lcd.setTextSize(2);

        const int lineHeight = 32;
        const int centerY = lcd.height() / 2;

        lcd.drawString(
            "TEMP: " +
                String(_data.temperature, 1) +
                " C",
            lcd.width() / 2,
            centerY - lineHeight
        );

        lcd.drawString(
            "HUM: " +
                String(_data.humidity, 1) +
                " %",
            lcd.width() / 2,
            centerY
        );

        lcd.drawString(
            "AIR: " +
                String(_data.airQuality),
            lcd.width() / 2,
            centerY + lineHeight
        );
    }

    /*
     * -------------------------------------------------
     * PAGE 1 — EVENT LOG
     * -------------------------------------------------
     *
     * Надпись EVENTS убрана.
     *
     * 4 строки событий располагаются единым блоком
     * строго по центру экрана.
     *
     * Индикатор батареи не выводим.
     */
    else
    {
        lcd.setFont(&fonts::Font0);
        lcd.setTextSize(2);

        const int lineHeight = 27;
        const int eventCount = 4;

        const int totalHeight =
            lineHeight * (eventCount - 1);

        const int centerY =
            lcd.height() / 2;

        const int startY =
            centerY - (totalHeight / 2);

        for (
            uint8_t i = 0;
            i < _data.eventCount && i < 4;
            ++i
        )
        {
            const StatisticsEventView& event =
                _data.events[i];

            String type;

            if (
                event.type ==
                StatisticsType::Light
            )
            {
                type = "LIGHT";
            }
            else
            {
                type = "FAN";
            }

            String state;

            if (
                event.state ==
                StatisticsEventState::On
            )
            {
                state = "ON";
            }
            else
            {
                state = "OFF";
            }

            lcd.drawString(
                String(event.time) +
                    " " +
                    type +
                    " " +
                    state,
                lcd.width() / 2,
                startY + i * lineHeight
            );
        }

        if (_data.eventCount == 0)
        {
            lcd.drawString(
                "NO EVENTS",
                lcd.width() / 2,
                centerY
            );
        }
    }

    renderer.update();
}