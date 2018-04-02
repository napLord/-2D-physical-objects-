#include "world.h"

using namespace sf;


World::World(sf::RenderWindow &window, b2Vec2 gravity)
    : mWindow(window), mWorld(*(new b2World(gravity))), mFabric("1.png")
{
    mGravity = gravity;
    mItemType = RECTANGLE;

    mBType = DYNAMIC;

    mPItem = 0;
    mSelectedItem = 0;

    isPaused = false;

    setMap();

    setBG(0);
}



void World::upadate(int fps)
{
    if(!isPaused)
    {
        mWorld.Step((float)1/fps, 8, 3);  //8 and 3 - precising.

        if(mSelectedItem)
            dragItem(mSelectedItem);

    }

    draw();
}





void World::clickHandle(float x, float y)
{
    if(mSelectedItem)   //if dragging something
    {
        mSelectedItem->setSelected(0);
        mSelectedItem = 0;
    }
    else
    {
        Item *foundedItem = getItem(x,y);

        if(foundedItem && foundedItem->getBType() == DYNAMIC)
        {
            mSelectedItem = foundedItem;
            mSelectedItem->setSelected(1);
        }
        else
            createItem(x,y,mBType);
    }
}

void World::createItem(float x, float y, BType bType)
{
     mItems.push_back(mFabric.create(mWorld,x,y,30,30,bType, mItemType, "blankName"));
}

void World::setBehaviourType(BType type)
{
    mBType = type;
}



void World::setItemType(ItemType type)
{
    mItemType = type;

}

void World::dragEnterHandle(float x, float y)
{
    mPItem = dynamic_cast<PreviewItem*>(mFabric.create
                                        (mWorld, x, y, 5, 5, mBType,
                                         (mItemType == RECTANGLE) ? PREVIEW_RECTANGLE : PREVIEW_CIRCLE ));
}

void World::dragLeaveHandle()
{
    mItems.push_back(mFabric.create(mPItem));
    delete mPItem;
    mPItem = 0;
}

void World::dragMoveHandle(float x, float y)
{
    mPItem->updateSizeWithPoint(x,y);
}

void World::dragItem(Item *item)
{
    item->move(sf::Mouse::getPosition(mWindow).x, sf::Mouse::getPosition(mWindow).y);


}

void World::setGravity(float x, float y)
{
    mGravity = b2Vec2(x,y);
    mWorld.SetGravity(mGravity);

}

void World::clear()
{
    for(Item* i : mItems)
        mWorld.DestroyBody(i->getBody());
    mItems.clear();
    setMap();
}

void World::undo()
{
    if(mItems.size()>1)        //1st item is ground, so u can't delete the ground
    {
        mWorld.DestroyBody(mItems[mItems.size()-1]->getBody());
        mItems.pop_back();
    }
}

void World::setBG(int num)
{
    static sf::Sprite bG;
    bG.setPosition(0,0);

    static sf::Texture zero;
    static sf::Texture one;
    static sf::Texture two;

    zero.loadFromFile("zero.png");
    one.loadFromFile("one.png");
    two.loadFromFile("two.png");
    zero.setRepeated(true);
    one.setRepeated(true);
    two.setRepeated(true);

    switch(num)
    {
        case 0:
        {
            bG.setTexture(zero);
            bG.setTextureRect(IntRect(0,0,1280,720));
            mBackground = bG;
            break;
        }
        case 1:
        {
            bG.setTexture(one);
            bG.setTextureRect(IntRect(0,0,1280,720));
            mBackground = bG;
            break;
        }
        case 2:
        {
            bG.setTexture(two);
            bG.setTextureRect(IntRect(0,0,1280,720));
            mBackground = bG;
            break;
        }
        default:
            throw;
    }
}

void World::setAllItemsRestitution(float r)
{
    for(Item* i : mItems)
        i->setRestitution(r);

}

void World::setPaused()
{
    isPaused = (isPaused == true) ? false : true;
}



Item* World::getItem(float x, float y)
{
    for(Item* i : mItems)
        if (i->getBody()->GetFixtureList()->TestPoint(b2Vec2(x/SCALE,y/SCALE)))
        {
            return i;
        }

    return 0;
}

void World::draw()
{
    mWindow.draw(mBackground);

    for(auto i : mItems)
        i->draw(mWindow);

    if(mPItem)
        mPItem->draw(mWindow);

}

void World::setMap()
{
    mItems.push_back(mFabric.create(mWorld,640,720,800,35,STATIC, RECTANGLE, "GROUND"));

}
