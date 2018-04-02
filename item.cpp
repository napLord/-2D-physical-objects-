#include "item.h"


Item::Item(b2World &world, float x, float y, float w, float h,
           BType type, sf::String data, sf::Sprite sprite)
    : mWorld(world)
{
    mX = x; mY = y; mW = w; mH = h;
    mData = data; mType = type;
    mState = UNSELECTED;

    mSprite = sprite;
    mSprite.setOrigin(sprite.getTextureRect().width/2,
                      sprite.getTextureRect().height/2);
    mSprite.setScale((2*w)/sprite.getTextureRect().width,
                     (2*h)/sprite.getTextureRect().height);

}

void Item::draw(sf::RenderWindow &window)
{
    update();

    window.draw(mSprite);
}

b2World &Item::getWorld()
{
    return mWorld;
}

sf::Sprite Item::getSprite()
{
    return mSprite;
}

sf::String Item::getData()
{
    return mData;
}

BType Item::getBType()
{
    return mType;
}

float Item::getX()
{
    return mX;
}

float Item::getY()
{
    return mY;
}

float Item::getW()
{
    return mW;
}

float Item::getH()
{
    return mH;
}

 b2Body *Item::getBody()
{
    return mItem;
}

void Item::setSelected(bool state)
{
    mState = (state == true) ? SELECTED : UNSELECTED;
}

void Item::move(float x, float y)
{
    float xForce = (x - mX)/SCALE;
    float yForce = (y - mY)/SCALE;


    //some heuristics(magic) to smooth moving
    if(abs(xForce) >0.4)
        xForce += 3*xForce/abs(xForce);
    if(abs(yForce) >0.4)
        yForce += 3*yForce/abs(yForce);
    if(abs(xForce) <1)
        xForce *= 10;
    if(abs(yForce) <1)
        yForce *= 10;
    xForce = xForce * abs(xForce); yForce = yForce * abs(yForce);



    mItem->SetLinearVelocity(b2Vec2(xForce, yForce));
}

void Item::setRestitution(float r)
{
    if((r <= 1) && (r >= 0))
        mItem->GetFixtureList()->SetRestitution(r);
    else
        return;
}

void Item::update()
{
    b2Vec2 pos = mItem->GetPosition();
    float angle = mItem->GetAngle();

    mX = pos.x*SCALE; mY = pos.y*SCALE;

    mSprite.setPosition(pos.x*SCALE, pos.y*SCALE);
    mSprite.setRotation(angle*DEG);

    if(mState == SELECTED)
        mSprite.setColor(sf::Color(255,100,100,200));
    else
        mSprite.setColor(sf::Color::White);
}

Fabric::Fabric(sf::String fileName)
{
    fileName = "1.png";

    mTexture = sf::Texture();
    mTexture.loadFromFile(fileName);
    mTexture.setSmooth(true);

    mRecRect = sf::IntRect(0,0,150,150);
    mRecSprite = sf::Sprite(mTexture);
    mRecSprite.setTextureRect(mRecRect);

    mCircleRect = sf::IntRect(151,0,149,150);
    mCircleSprite = sf::Sprite(mTexture);
    mCircleSprite.setTextureRect(mCircleRect);

}

Item *Fabric::create(b2World &world, float x, float y, float w, float h, BType bType, ItemType iType, sf::String data, float density, float friction)
{
    switch(iType)
    {
        case RECTANGLE:
            return new RectangleItem(world,x,y,w,h,bType,"RECTANGLE",mRecSprite);
            break;

        case CIRCLE:
            return new CircleItem(world,x,y,w,h,bType,"CIRCLE",mCircleSprite);
            break;


        case PREVIEW_RECTANGLE:
            return new PreviewItem(world,x,y,bType,"P_RECTANGLE",mRecSprite);
            break;

        case PREVIEW_CIRCLE:
            return new PreviewItem(world,x,y,bType,"P_CIRCLE",mCircleSprite);
            break;




        default:
        {
            throw;
        }
    }
}

Item *Fabric::create(Item *item)
{
    sf::String name = item->getData();
    b2World &world = item->getWorld();
    float x = item->getX();
    float y = item->getY();
    float w = item->getW();
    float h = item->getH();
    sf::Sprite sprite = item->getSprite();
    BType bType = item->getBType();

    if(name == "P_RECTANGLE")
        return create(world, x, y, w, h, bType, RECTANGLE , "RECTANGLE");
    if(name == "P_CIRCLE")
        return create(world, x, y, w, h, bType, CIRCLE , "CIRCLE");

    throw;
}



RectangleItem::RectangleItem(b2World &world, float x, float y, float w, float h, BType type, sf::String data, sf::Sprite sprite, float density, float friction)
    :Item(world, x, y, w, h, type, data, sprite)
{
    mDensity = density;
    mFriction = friction;
    itemCreation();
}

void RectangleItem::itemCreation()
{
    b2PolygonShape *shape = new b2PolygonShape;
    shape->SetAsBox(mW/SCALE,mH/SCALE);
    mShape = shape;

    b2BodyDef bDef;
    bDef.position.Set((float)mX/SCALE, (float)mY/SCALE);
    if(mType == DYNAMIC)
            bDef.type = b2_dynamicBody;
    mItem = mWorld.CreateBody(&bDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = mShape;
    fixtureDef.density = mDensity;
    fixtureDef.friction = mFriction;

    mItem->CreateFixture(&fixtureDef);
}


CircleItem::CircleItem(b2World &world, float x, float y, float w, float h, BType type, sf::String data, sf::Sprite sprite, float density, float friction)
    :Item(world, x, y, w, h, type, data, sprite)
{
    mDensity = density;
    mFriction = friction;
    itemCreation();
}

void CircleItem::itemCreation()
{
    b2CircleShape *shape = new b2CircleShape;
    shape->m_radius = mW/SCALE;
    mShape = shape;

    b2BodyDef bDef;
    bDef.position.Set((float)mX/SCALE, (float)mY/SCALE);
    if(mType == DYNAMIC)
            bDef.type = b2_dynamicBody;
    mItem = mWorld.CreateBody(&bDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = mShape;
    fixtureDef.density = mDensity;
    fixtureDef.friction = mFriction;

    mItem->CreateFixture(&fixtureDef);
}

PreviewItem::PreviewItem(b2World &world, float x, float y, BType bType, sf::String data, sf::Sprite sprite)
    :Item(world,x,y,5,5,bType,data,sprite)
{
    itemCreation();
}

void PreviewItem::itemCreation()
{
    mSprite.setColor(sf::Color(150,150,150,55));
    mSprite.setPosition(mX,mY);
}

void PreviewItem::update()
{
    mSprite.setScale((2*mW)/mSprite.getTextureRect().width,
                            (2*mH)/mSprite.getTextureRect().height);
}

void PreviewItem::updateSizeWithPoint(float x, float y)
{
    mW = abs(mX - x );
    if(mData == "P_CIRCLE")
        mH = abs(mX - x);
    else
        mH = abs(mY - y);
}
