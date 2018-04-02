#include "app.h"

App::App(VideoMode videoMode, int fps, String name)
{
    mMode = videoMode;
    mFps = fps;
    mName = name;
    mIsDragging = 0;
}

void App::run()
{
    sf::RenderWindow window(mMode, mName);
    mWindow = &window ;
    mWindow->setFramerateLimit(mFps);

    mWorld = new World(*mWindow, b2Vec2(0.f, 9.8f));

    ImGui::SFML::Init(*mWindow);

    deltaClock.restart();

    appCycling();
}

void App::appCycling()
{
    while (mWindow->isOpen())
    {
        mWindow->resetGLStates();

        mWindow->clear(sf::Color::White);

        eventHandle();

        mWorld->upadate(mFps);

        guiUpdate();

        mWindow->display();
    }
}

void App::guiUpdate()
{
    static float g = 9.8;
    static float r = 0;
    static int cItem = 0; char items[] = "Rectangle\0Circle\0";
    static int cBItem = 0; char bItems[] = "Dynamic\0Static\0";
    static int cBackG = 0; char bGItems[] = "Rects\0Not so cool rects\0Cool rects\0";

    ImGui::SFML::Update(*mWindow, deltaClock.restart());

    ImGui::Begin("Sample window");

    mGuiRect.left = ImGui::GetWindowPos().x;
    mGuiRect.top = ImGui::GetWindowPos().y;
    mGuiRect.width = ImGui::GetWindowWidth();
    mGuiRect.height = ImGui::GetWindowHeight();

    if (ImGui::DragFloat("Gravity", &g, 0.1 , 0.f, 100.f))
    {
        mWorld->setGravity(0, g);
    }

    if (ImGui::Combo("Items", &cItem, items, 2))
    {
        mWorld->setItemType((cItem == 0) ? RECTANGLE : CIRCLE);

    }

    if (ImGui::Combo("Items behaviour", &cBItem, bItems, 2))
    {
        mWorld->setBehaviourType((cBItem == 0) ? DYNAMIC : STATIC);

    }

    if (ImGui::Combo("Background", &cBackG, bGItems, 3))
    {
        mWorld->setBG(cBackG);
    }


    if (ImGui::DragFloat("Restitution", &r, 0.01 , 0.f, 1.f))
    {
        mWorld->setAllItemsRestitution(r);
    }

    if (ImGui::Button("Clear",ImVec2(50,20)))
    {
        mWorld->clear();
    }

    if (ImGui::Button("Pause",ImVec2(50,20)))
    {
        mWorld->setPaused();
    }

    ImGui::End();

    ImGui::Render();
}

void App::eventHandle()
{
    sf::Event e;

    while (mWindow->pollEvent(e))
    {
        ImGui::SFML::ProcessEvent(e);


        if (e.type == Event::Closed)
        {
            mWindow->close();
        }

        if(e.type == Event::MouseButtonPressed &&
                mGuiRect.contains( e.mouseButton.x, e.mouseButton.y))
        {
            continue;
        }
        if (e.type == Event::MouseButtonPressed &&
                e.mouseButton.button == sf::Mouse::Button::Left)
        {
            mWorld->clickHandle(e.mouseButton.x,e.mouseButton.y);
        }

        if (e.type == Event::MouseButtonPressed &&
                e.mouseButton.button == sf::Mouse::Button::Right)
        {
            mWorld->dragEnterHandle(e.mouseButton.x,e.mouseButton.y);
            mIsDragging = true;
        }

        if (e.type == Event::MouseButtonReleased &&
                e.mouseButton.button == sf::Mouse::Button::Right)
        {
            mWorld->dragLeaveHandle();
            mIsDragging = false;
        }

        if (e.type == Event::MouseMoved && mIsDragging)
        {
            mWorld->dragMoveHandle(e.mouseMove.x, e.mouseMove.y);
        }

        if (e.type == Event::KeyPressed)
        {
            switch (e.key.code)
            {
                case sf::Keyboard::X:
                    mWorld->undo();
            }
        }
    }

}
