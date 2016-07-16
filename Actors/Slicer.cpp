//
//  Slicer.cpp
//  OTap
//
//  Created by Sebastian on 16/07/16.
//
//

#include "Slicer.hpp"
#include "Definitions.h"
#include <cmath>

USING_NS_CC;

Slicer::Slicer() {}

Slicer::~Slicer() {}

Slicer* Slicer::create(int type)
{
    Slicer *pSprite = new Slicer();
    if (pSprite->initWithFile("slicer.png"))
    {
        pSprite->autorelease();
        pSprite->initWithOptions(type);
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Slicer::initWithOptions(int type)
{
    this->type = type;
    
    winSize = Director::getInstance()->getWinSize();
    minSize = SMIN * winSize.x / 100;
    maxSize = SMAX * winSize.x / 100;
    
    if(winSize.x < winSize.y)
    {
        speed = winSize.x / SSPEED;
    }
    else{
        speed = winSize.y / SSPEED;
    }
    
    spawnSlicer();
}

void Slicer::spawnSlicer()
{
    
    int sz = RandomHelper::random_int(minSize, maxSize);
    r = sz/2;
    
    this->setAnchorPoint(Vec2(0.5,0.5));
    float scale = (sz)/(this->getContentSize().width);
    this->setScale(scale);
    
    int x1Pos, y1Pos, x2Pos, y2Pos;
    if(type == 0)
    {
        x1Pos = sz/2;
        y1Pos = RandomHelper::random_int(sz, (int) winSize.y - sz);
        x2Pos = winSize.x + sz;
        y2Pos = RandomHelper::random_int(sz, (int) winSize.y - sz);
        
    }
    else
    {
        x2Pos = -sz;
        y2Pos = RandomHelper::random_int(sz, (int) winSize.y - sz);
        x1Pos = winSize.x - sz/2;
        y1Pos = RandomHelper::random_int(sz, (int) winSize.y - sz);
    }
    
    
    this->setPosition(x1Pos, y1Pos);
    
    float moveTime = getDist(x1Pos, y1Pos, x2Pos, y2Pos) / speed;
    
    
    auto rotateBy = RotateBy::create(1.0f, 360.0f);
    auto rotateBy1 = RotateBy::create(moveTime, moveTime*360.0f);
    auto moveTo = MoveTo::create(moveTime, Vec2(x2Pos, y2Pos));
    
    auto spawn = Spawn::createWithTwoActions(rotateBy1,moveTo);
    
    auto sq1 = Sequence::create(rotateBy,spawn,NULL);
    this->runAction(sq1);
}

bool Slicer::isOutOfScreen()
{
    if(this->getPosition().x < -r|| this->getPosition().x > winSize.x + r)
        return true;
    else if (this->getPosition().y < -r || this->getPosition().y > winSize.y + r)
        return true;
    else
        return false;
}

int Slicer::getDist(int x1, int y1, int x2, int y2)
{
    int d2 = ((x2-x1) * (x2 - x1)) + ((y2-y1) * (y2 - y1));
    int d = std::sqrt(d2);
    
    return d;
}
int Slicer::getRadius()
{
    return r;
}