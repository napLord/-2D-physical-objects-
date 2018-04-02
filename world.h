/*World managing physics, item storaging, click handling and so on*/
#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <Box2D.h>
#include <Graphics.hpp>
#include <Window.hpp>

#include "item.h"




class World
{
public:
    World(sf::RenderWindow &window, b2Vec2 gravity);
    Item *getItem(float x, float y);
    void upadate(int fps);
    void setItemType(ItemType type);
    void clickHandle(float x, float y);
    void createItem(float x, float y, BType bType);
    void setBehaviourType(BType type);
    void dragEnterHandle(float x, float y);
    void dragLeaveHandle();
    void dragMoveHandle(float x, float y);
    void dragItem(Item*item);
    void setGravity(float x, float y);
    void clear();
    void undo();
    void setBG(int num);
    void setAllItemsRestitution(float r);
    void setPaused();

private:
    void draw();
    void setMap();

    sf::RenderWindow &mWindow;
    b2World &mWorld;
    b2Vec2 mGravity;
    ItemType mItemType;
    BType mBType;                      //behaviour type
    std::vector<Item*> mItems;
    Fabric mFabric;
    PreviewItem *mPItem;
    Item *mSelectedItem;
    sf::Sprite mBackground;
    bool isPaused;


};

#endif // WORLD_H
