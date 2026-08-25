#include "ButtonManager.h"

void ButtonManager::begin()
{
    pinMode(NEXT_PIN, INPUT_PULLUP);
    pinMode(ACTION_PIN, INPUT_PULLUP);

    _nextState = digitalRead(NEXT_PIN);
    _actionState = digitalRead(ACTION_PIN);

    _nextChangeTime = millis();
    _actionChangeTime = millis();

    _nextPressed = false;
    _actionPressed = false;
}

void ButtonManager::update()
{
    _nextPressed = false;
    _actionPressed = false;

    if (updateButton(
            NEXT_PIN,
            _nextState,
            _nextChangeTime))
    {
        _nextPressed = true;
    }

    if (updateButton(
            ACTION_PIN,
            _actionState,
            _actionChangeTime))
    {
        _actionPressed = true;
    }
}

bool ButtonManager::updateButton(
    uint8_t pin,
    bool& lastState,
    uint32_t& lastChangeTime)
{
    const bool currentState =
        digitalRead(pin);

    const uint32_t now = millis();

    if (currentState == lastState)
    {
        return false;
    }

    if (now - lastChangeTime < DEBOUNCE_TIME)
    {
        return false;
    }

    lastChangeTime = now;

    const bool wasReleased =
        lastState == HIGH;

    lastState = currentState;

    // Событие только в момент нажатия:
    // HIGH -> LOW
    if (wasReleased && currentState == LOW)
    {
        return true;
    }

    return false;
}

bool ButtonManager::isNextPressed() const
{
    return _nextPressed;
}

bool ButtonManager::isActionPressed() const
{
    return _actionPressed;
}