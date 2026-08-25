#pragma once

#include "controllers/MainController.h"

class Application
{
public:
    static void setup();
    static void loop();

private:
    static MainController controller;
};