//
//  Spot.cpp
//  OTap
//
//  Created by Sebastian on 02/07/16.
//
//

#include "Spot.hpp"
#include "Definitions.h"
#include <cmath>

USING_NS_CC;

Spot::Spot() {};

Spot::~Spot() {};

Spot* Spot::create(String fname)
{
    Spot *pSpot = new Spot();
    if(pSpot->initWithFile(fname.getCString()))
    {
        pSpot->autorelease();
        pSpot->initOptions();
        pSpot->addEvents();
        return pSpot;
    }
    
    CC_SAFE_DELETE(pSpot);
    return NULL;
}

void Spot::initOptions()
{
    winSize = Director::getInstance()->getWinSize();
    defSize = (SPOT_SIZE * winSize.y)/(100*2);
    currSize = defSize;
    this->swiped = false;
    this->play = true;
    
    this->setAnchorPoint(Vec2(0.5,0.5));
    float scale = (SPOT_SIZE* winSize.x)/(this->getContentSize().width * 100);
    this->setScale(scale);
    this->setPosition(winSize.x/2, winSize.y/2);
}


void Spot::addEvents()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Spot::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Spot::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Spot::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(Spot::onTouchesEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Spot::addArea(int r)
{

    float currentArea =  (this->getBoundingBox().size.width/2 ) * (this->getBoundingBox().size.width/2);/* *3.14 */
    float extraArea = r * r; /* "* 3.14 */
    
    int newArea = currentArea + extraArea;
    int newRad = std::sqrt(newArea);
    
    this->setToRadius(newRad);
}

void Spot::stopPlay()
{
    this->play = false;
}

void Spot::reduceSize()
{
    this->runAction(ScaleBy::create(0.3f, 0.9f));
    //CCLOG("Reduce size");
}


void Spot::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    // reset touch offset
    this->touchOffset = Point::ZERO;
    for( auto touch : touches )
    {
        // if this touch is within our sprite's boundary
        if(play && touch && this->isTouchingSpot(touch) )
        {
            // calculate offset from sprite to touch point
            this->touchOffset = this->getPosition() - this->touchToPoint(touch);
        }
    }
}

void Spot::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    for( auto touch : touches )
    {
        // set the new sprite position
        if( play && touch && touchOffset.x && touchOffset.y )
        {
            Point p = this->getInScreenPoint(this->touchToPoint(touch) + this->touchOffset);
            this->setPosition(p);
            this->swiped = true;
        }
        
    }
}

void Spot::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for( auto touch : touches )
    {
        if( play && touch && touchOffset.x && touchOffset.y  )
        {
            // set the new sprite position
            Point p = this->getInScreenPoint(this->touchToPoint(touch) + this->touchOffset);
            this->setPosition(p);
            this->reduceSize();
            // stop any existing actions and reset the scale
            //this->stopAllActions();
        }
    }
}

Point Spot::getInScreenPoint(Point p)
{
    Vec2 minScreenPoint = Vec2(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height/2);
    Vec2 maxScreenPoint = Vec2(this->winSize.x - this->getBoundingBox().size.width/2,
                               this->winSize.y - this->getBoundingBox().size.height/2);
    
    p.clamp(minScreenPoint, maxScreenPoint);
    return p;
}

bool Spot::isTouchingSpot(Touch *touch)
{
    return (this->getPosition().getDistance(this->touchToPoint(touch)) < this->getBoundingBox().size.width/2);
}

Point Spot::touchToPoint(Touch *touch)
{
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

void Spot::setToRadius(int r)
{
    //float scale = (r* winSize.height)/(citem->getContentSize().height);
    float scale = (2*r)/this->boundingBox().size.width;
    this->runAction(ScaleBy::create(0.3f, scale));
    this->currSize = this->getContentSize().width;
}
