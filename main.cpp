#include <iostream>

#include "app.h"


int main()
{
    int height = 720, width = 1280;

    App mApp(sf::VideoMode(width, height, 32), 60, "Test");
    mApp.run();

    return 0;
}
