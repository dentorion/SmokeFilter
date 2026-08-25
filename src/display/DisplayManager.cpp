#include "DisplayManager.h"

#include "../screens/Screen.h"

bool DisplayManager::begin()
{
    return _renderer.begin();
}

void DisplayManager::show(Screen& screen)
{
    _renderer.clear();

    screen.draw(_renderer);

    _renderer.update();
}

DisplayRenderer& DisplayManager::renderer()
{
    return _renderer;
}