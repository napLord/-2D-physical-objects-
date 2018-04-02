/*SFML provides graphics, and b2D provides physics.
 * Item is purposed to combine b2Body and sfml sprite to create
 * a new entity that you can use as a physical body with b2D
 * and a sfml graphical object*/
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <math.h>
#include <Box2D.h>
#include <Graphics.hpp>
#include <Window.hpp>


enum BType{DYNAMIC, STATIC};
enum ItemType{RECTANGLE,CIRCLE,PREVIEW_RECTANGLE,PREVIEW_CIRCLE};
enum State{SELECTED,UNSELECTED};

const float SCALE = 30.f;      //b2D works with meters, 1m = 30px
const float DEG  =  57.29577f; //b2D works with rads 1rad ~ 57 deg




class Item
{
public:
    Item(b2World &world, float x, float y, float w, float h, BType type,
         sf::String data, sf::Sprite sprite);
    virtual void draw(sf::RenderWindow & window);
    virtual b2World& getWorld();
    virtual sf::Sprite getSprite();
    virtual sf::String getData();
    virtual BType getBType();
    virtual float getX();
    virtual float getY();
    virtual float getW();
    virtual float getH();
    virtual b2Body *getBody();
    virtual void setSelected(bool state);
    virtual void move(float x, float y);
    virtual void setRestitution(float r);
protected:
    virtual void update();      //updating coords according to mItem's coords.
    virtual void itemCreation() = 0 ;

    b2Body *mItem;              //main phys entity
    b2World &mWorld;
    b2Shape *mShape;     //shape
    sf::Sprite mSprite;
    sf::String mData;           //name or something like that
    BType mType;                //dynamic or static phys body
    State mState;
    float mX, mY, mW, mH;
    float mDensity;
    float mFriction;

};

class RectangleItem : public Item
{
public:
    RectangleItem(b2World &world, float x, float y, float w, float h, BType type,
                  sf::String data, sf::Sprite sprite, float density = 1, float friction = 0.3);

protected:
    virtual void itemCreation();

};


class CircleItem : public Item
{
public:
    CircleItem(b2World &world, float x, float y, float w, float h, BType type,
                  sf::String data, sf::Sprite sprite, float density = 1, float friction = 0.3);

protected:
    virtual void itemCreation();


};

class PreviewItem : public Item
{
public:
    PreviewItem(b2World &world, float x, float y, BType bType,
                  sf::String data, sf::Sprite sprite);
    void updateSizeWithPoint(float x, float y);

protected:
    virtual void itemCreation();
    virtual void update();


};

class Fabric
{
public:
    Fabric(sf::String fileName);
    Item* create(b2World &world, float x, float y, float w = 5, float h = 5, BType bType = STATIC,
                 ItemType iType = RECTANGLE, sf::String data = "NULL", float density = 1, float friction = 0.3 );
    Item* create(Item*item);

private:
    sf::Texture mTexture;

    sf::Sprite mRecSprite;
    sf::IntRect mRecRect;

    sf::Sprite mCircleSprite;
    sf::IntRect mCircleRect;
};



#endif // ITEM_H
