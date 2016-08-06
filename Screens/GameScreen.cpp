//
//  GameScreen.cpp
//  OTap
//
//  Created by Sebastian on 22/06/16.
//
//

#include "GameScreen.h"
#include "ui/CocosGUI.h"
#include "../Definitions.h"
#include "../Actors/Spot.hpp"
#include "../Actors/Particle.hpp"
#include "../Actors/KillerCircle.hpp"
#include "../Screens/MenuScreen.hpp"
#include "../Screens/GameOverScreen.hpp"


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
    
    this->score = 0;
    this->level = 0;
    
    this->levelLabel = ui::Text::create(u.scoreAsStr(this->score), "Circular Abstracts.ttf", 128);
    this->levelLabel->setScale(winSize.width/(this->levelLabel->getContentSize().width*10));
    this->levelLabel->setAnchorPoint(Vec2(0.0f,0.0f));
    this->levelLabel->setPosition(Vec2(2,2));
    this->levelLabel->setColor(Color3B(255,255,255));
    
    levelScoreBar = ui::LoadingBar::create("progressbar.png");
    //levelScoreBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    levelScoreBar->setAnchorPoint(Vec2(0,1));
    levelScoreBar->setScale(winSize.width/levelScoreBar->getContentSize().width,
                            winSize.height/(100*levelScoreBar->getContentSize().height));
    levelScoreBar->setPosition(Vec2(0,winSize.height));
    levelScoreBar->setSize(Size(winSize.width,winSize.height/20));
    levelScoreBar->setPercent(0.0f);
    
    
    
    this->layerColor = new LayerColor;
    this->layerColor->initWithColor(u.getBgColor(RandomHelper::random_int(0,BGColors-1)));
    this->addChild(this->layerColor, 1);
    
    this->addChild(levelLabel,3);
    this->addChild(levelScoreBar,3);
    
    //intialize the spot
    initSpot();
    initParticles();
    addSlicer();
    addKillerCircle();
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
            //CCLOG("Game Over");
            auto scene = GameOverScreen::createScene(level);
            Director::getInstance()->replaceScene(scene);
        }
    }
    
    Vector<KillerCircle *> kctoDelete;
    for( auto kc : killerCircles)
    {
        if(kc->getBoundingBox().intersectsRect(spot->getBoundingBox()))
        {
            if(kc->isWhite())
            {
                addScore(3);
            }
            else
            {
                auto scene = GameOverScreen::createScene(level);
                Director::getInstance()->replaceScene(scene);
            }
            kctoDelete.pushBack(kc);
        }
    }
    for(auto kcDel : kctoDelete)
    {
        if (kctoDelete.contains(kcDel))
        {
            killerCircles.erase(killerCircles.find(kcDel));
            this->removeChild(kcDel);
            addKillerCircle();
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
                addScore(1);
                //score = score + pdel->getScore();
                particles.erase(particles.find(pdel));
                this->removeChild(pdel);
                addParticle();
            }
        }
        
    }
}

void GameScreen::addScore(int s)
{
    score += s;
    if (score >= u.getLevelScoreNeeded(level)){
        score = 0;
        level++;
    }
    levelLabel->setText(u.scoreAsStr(level));
    float percent = score/(float)u.getLevelScoreNeeded(level);
    percent = percent * 100;
    //CCLOG("percent %f , score %d, fromLevel %d",percent,score, u.getLevelScoreNeeded(level) );
    levelScoreBar->setPercent(percent);

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

void GameScreen::resetKillerCircles()
{
    int num = u.getNumKillerCircles(level);
}

void GameScreen::addKillerCircle()
{
    KillerCircle *kc = KillerCircle::create();
    this->addChild(kc,2);
    killerCircles.pushBack(kc);
}

void GameScreen::addParticle()
{
    Particle *p = Particle::create();
    this->addChild(p,2);
    particles.pushBack(p);
}

void GameScreen::initSpot ( )
{
    spot  = Spot::create("wcircle.png");
    spot->setPosition(winSize.width/4, winSize.height/4);
    this->addChild(spot,2);
}

