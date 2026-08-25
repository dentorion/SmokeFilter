#include "Application.h"

#include "database/Database.h"

MainController Application::controller;

void Application::setup()
{
    Database::begin();

    controller.begin();
}

void Application::loop()
{
    controller.update();
}