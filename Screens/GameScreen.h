//
//  GameScreen.h
//  OTap
//
//  Created by Sebastian on 22/06/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Actors/Particle.hpp"
#include "../Actors/Spot.hpp"
#include "../Actors/Slicer.hpp"
#include "../Actors/KillerCircle.hpp"
#include "../OUtility.h"


USING_NS_CC;

class GameScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int numtry, int level);
    virtual bool init();
    CREATE_FUNC(GameScreen);
    static int numtry;
    static int level;
    
    void update(float) override;
private:
    
    int score;
    int colorIndex;
    ui::Text *levelLabel;
    ui::LoadingBar *levelScoreBar;
    OUtility u;
    
    Size winSize;
    LayerColor *layerColor;
    
    Spot *spot;
    Vector<Particle *> particles;
    Vector<Slicer *> slicers;
    Vector<KillerCircle *> killerCircles;
        
    void initSpot();
    void initParticles();
    void addSlicer();
    void addParticle();
    void addKillerCircle();
    void setKillerCircles();
    
    void addScore(int s);
};
