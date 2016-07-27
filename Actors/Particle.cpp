//
//  Particle.cpp
//  OTap
//
//  Created by Sebastian on 02/07/16.
//
//

#include "Particle.hpp"
#include "Definitions.h"

USING_NS_CC;

Particle::Particle() {}

Particle::~Particle() {}

Particle* Particle::create()
{
    Particle *pSprite = new Particle();
    if (pSprite->initWithFile("cw.png"))
    {
        pSprite->autorelease();
        pSprite->initWithOptions();
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;    
}

void Particle::initWithOptions()
{
    winSize = Director::getInstance()->getWinSize();
    minSize = PMIN * winSize.x / 100;
    maxSize = PMAX * winSize.x / 100;
    
    int sz = RandomHelper::random_int(minSize, maxSize);
    r = sz/2;
    int xPos = RandomHelper::random_int(sz, (int) winSize.x - sz);
    int yPos = RandomHelper::random_int(sz, (int) winSize.y - sz);
    
    this->setAnchorPoint(Vec2(0.5,0.5));
    float scale = (sz)/(this->getContentSize().width);
    this->setScale(scale);
    this->setPosition(xPos, yPos);
    
    auto scaleBy1 = ScaleBy::create(1.0f,2.0f);
    auto scaleBy2 = ScaleBy::create(1.0f, 0.5f);
    auto sequence = Sequence::create(scaleBy2, scaleBy1, NULL);
    
    this->runAction(RepeatForever::create(sequence));
}

int Particle::getRadius()
{
    return r;
}