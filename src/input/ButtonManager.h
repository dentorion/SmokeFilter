#pragma once

#include <Arduino.h>

class ButtonManager
{
public:
    void begin();

    void update();

    bool isNextPressed() const;

    bool isActionPressed() const;

private:
    bool updateButton(
        uint8_t pin,
        bool& lastState,
        uint32_t& lastChangeTime
    );

private:
    // Кнопка NEXT
    static constexpr uint8_t NEXT_PIN = D6;

    // Кнопка ACTION
    static constexpr uint8_t ACTION_PIN = D0;

    static constexpr uint32_t DEBOUNCE_TIME = 40;

    bool _nextState = HIGH;
    bool _actionState = HIGH;

    uint32_t _nextChangeTime = 0;
    uint32_t _actionChangeTime = 0;

    bool _nextPressed = false;
    bool _actionPressed = false;
};