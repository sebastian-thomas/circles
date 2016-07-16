//
//  GameScreen.cpp
//  OTap
//
//  Created by Sebastian on 22/06/16.
//
//

#include "GameScreen.h"
#include "Definitions.h"
#include "Actors/Spot.hpp"
#include "Actors/Particle.hpp"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScreen::create();
    scene->addChild (layer);
    
    return scene;
}

bool GameScreen::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    
    this->layerColor = new LayerColor;
    this->layerColor->initWithColor( Color4B(70, 32, 102, 255) );
    this->addChild(this->layerColor, 1);
    
    //intialize the spot
    initSpot();
    initParticles();
    addSlicer();
    
    this->scheduleUpdate();
    return true;
}

void GameScreen::update(float dt)
{
    
    for (auto s : slicers)
    {
        if(s->isOutOfScreen())
        {
            s->spawnSlicer();
        }
        else if( s->getBoundingBox().intersectsRect(spot->getBoundingBox()))
        {
            CCLOG("Game Over");
        }
    }
    
    //check if spot overlaps with something
    if(spot != NULL)
    {
        Vector<Particle *> ptoDelete;
        for(auto p : particles)
        {
            if(p->getBoundingBox().intersectsRect(spot->getBoundingBox()))
            {
                ptoDelete.pushBack(p);
            }
        }
        
        for (auto pdel : ptoDelete)
        {
            if(particles.contains(pdel))
            {
                spot->addArea(pdel->getRadius());
                particles.erase(particles.find(pdel));
                this->removeChild(pdel);
                addParticle();
            }
        }
        
        if(ptoDelete.size() > 0){
            CCLOG("Remaining : %zd" ,particles.size());
        }
    }
}

void GameScreen::addSlicer()
{
    Slicer *s = Slicer::create(0);
    this->addChild(s,2);
    slicers.pushBack(s);
    
    Slicer *s2 = Slicer::create(1);
    this->addChild(s2,2);
    slicers.pushBack(s2);
}

void GameScreen::initParticles()
{
    for(int i=0; i < PINIT; ++i)
    {
        addParticle();
    }
    
}

void GameScreen::addParticle()
{
    Particle *p = Particle::create();
    this->addChild(p,2);
    particles.pushBack(p);
}

void GameScreen::initSpot ( )
{
    spot  = Spot::create("img/ball1.png");
    spot->setPosition(winSize.width/4, winSize.height/4);
    this->addChild(spot,2);
}
