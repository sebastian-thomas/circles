//
//  KillerCircle.cpp
//  OTap
//
//  Created by Sebastian on 03/08/16.
//
//

#include "KillerCircle.hpp"
#include "Definitions.h"
#include <cmath>

USING_NS_CC;

KillerCircle::KillerCircle() {}

KillerCircle::~KillerCircle() {}

KillerCircle* KillerCircle::create()
{
    KillerCircle *pSprite = new KillerCircle();
    if (pSprite->initWithFile("wcircle.png"))
    {
        pSprite->autorelease();
        pSprite->initWithOptions( );
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void KillerCircle::initWithOptions()
{
    
    winSize = Director::getInstance()->getWinSize();
    r = RandomHelper::random_int(PMIN,PMAX);
    
    int sz = r * winSize.x / 100;
    
    spawnKillerCircle(sz);
}

void KillerCircle::spawnKillerCircle(int sz)
{
    
    this->setAnchorPoint(Vec2(0.5,0.5));
    float scale = (sz)/(this->getContentSize().width);
    this->setScale(scale);
    
    int xPos, yPos;
    xPos = RandomHelper::random_int(sz, (int) winSize.x - sz);
    yPos = RandomHelper::random_int(sz, (int) winSize.y - sz);
    
    
    this->setPosition(xPos, yPos);
    
    //auto fadeIn = FadeIn::create(0.3f);
    //this->runAction(fadeIn);
    float initalSize = sz/10;
    
    isWhiteSprite = true;
    innerSprite = Sprite::create("bcircle.png");
    innerSprite->setAnchorPoint(Vec2(0.5f,0.5f));
    innerSprite->setPosition(0,0);
    innerSprite->setScale(initalSize/innerSprite->getContentSize().width);
    Vec2 worldPosition = this->convertToNodeSpace(this->getPosition());
    innerSprite->setPosition(worldPosition);
    
    auto toggleSprite = CallFunc::create([this,initalSize](){
        //log("Rotated!");
        this->toggleCircle(initalSize);
    });
    
    
    auto scaleBy = ScaleTo::create(2.0f,1.0f);
    //innerSprite->runAction(scaleBy);
    
    auto seq1 = Sequence::create(scaleBy, toggleSprite, nullptr);
    innerSprite->runAction(RepeatForever::create(seq1));
    
    this->addChild(innerSprite);
}

void KillerCircle::toggleCircle(int initalSize)
{
    if(isWhiteSprite)
    {
        this->setTexture("bcircle.png");
        this->innerSprite->setTexture("wcircle.png");
        this->innerSprite->setScale(initalSize/innerSprite->getContentSize().width);
        isWhiteSprite = false;
    }
    else{
        this->setTexture("wcircle.png");
        this->innerSprite->setTexture("bcircle.png");
        this->innerSprite->setScale(initalSize/innerSprite->getContentSize().width);
        isWhiteSprite = true;
    }
}

bool KillerCircle::isOutOfScreen()
{
    if(this->getPosition().x < -r|| this->getPosition().x > winSize.x + r)
        return true;
    else if (this->getPosition().y < -r || this->getPosition().y > winSize.y + r)
        return true;
    else
        return false;
}

bool KillerCircle::isWhite()
{
    return isWhiteSprite;
}

int KillerCircle::getDist(int x1, int y1, int x2, int y2)
{
    int d2 = ((x2-x1) * (x2 - x1)) + ((y2-y1) * (y2 - y1));
    int d = std::sqrt(d2);
    
    return d;
}
int KillerCircle::getRadius()
{
    return r;
}