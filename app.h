/*Main application. Managing Events, SFML window and SFML cycle
Usage: create APP by constructor, then just run it by run().*/
#ifndef APP_H
#define APP_H

#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <Box2D.h>
#include <Graphics.hpp>
#include <Window.hpp>

#include "world.h"




using namespace sf;

class App
{
public:
    App(sf::VideoMode videoMode, int fps, sf::String name);
    void run();

private:
    void eventHandle();
    void appCycling();
    void guiUpdate();

    World *mWorld;
    sf::RenderWindow *mWindow;
    sf::VideoMode mMode;
    int mFps;
    sf::String mName;
    bool mIsDragging;
    sf::Clock deltaClock;
    sf::IntRect mGuiRect;
};

#endif // APP_H
