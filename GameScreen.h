//
//  GameScreen.h
//  OTap
//
//  Created by Sebastian on 22/06/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Actors/Particle.hpp"
#include "Actors/Spot.hpp"
#include "Actors/Slicer.hpp"

USING_NS_CC;

class GameScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScreen);
    
    void update(float) override;
private:
    
    Size winSize;
    LayerColor *layerColor;
    
    Spot *spot;
    Vector<Particle *> particles;
    Vector<Slicer *> slicers;
        
    void initSpot();
    void initParticles();
    void addSlicer();
    void addParticle();
};
