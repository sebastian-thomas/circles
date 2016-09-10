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

int GameScreen::numtry;
int GameScreen::level;

Scene* GameScreen::createScene(int numtry, int level)
{
    GameScreen::numtry = numtry;
    GameScreen::level = level;
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
    
    //this->score = 0;
    //this->level = 0;
    
    
    levelLabel = ui::Text::create(u.scoreAsStr(GameScreen::level), "Circular Abstracts.ttf", 128);
    levelLabel->setScale(winSize.width/(levelLabel->getContentSize().width*10));
    levelLabel->setAnchorPoint(Vec2(0.0f,0.0f));
    levelLabel->setPosition(Vec2(3,2));
    levelLabel->setColor(Color3B(255,255,255));
    
    levelScoreBar = ui::LoadingBar::create("progressbar.png");
    //levelScoreBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    levelScoreBar->setAnchorPoint(Vec2(0,1));
    levelScoreBar->setScale(winSize.width/levelScoreBar->getContentSize().width,
                            winSize.height/(100*levelScoreBar->getContentSize().height));
    levelScoreBar->setPosition(Vec2(0,winSize.height));
    levelScoreBar->setSize(Size(winSize.width,winSize.height/20));
    levelScoreBar->setPercent(0.0f);
    
    
    //this->colorIndex = RandomHelper::random_int(0,BGColors-1);
    this->colorIndex = 0;
    this->layerColor = new LayerColor;
    this->layerColor->initWithColor(u.getBgColor(colorIndex));
    this->addChild(this->layerColor, 1);
    
    
    
    //intialize the spot
    initSpot();
    initParticles();
    
    int numKC = u.getNumKillerCircles(level);
    for(int i=0; i < numKC; ++i)
    {
        addKillerCircle();
    }
    
    UserDefault *userDefault = UserDefault::getInstance();
    auto appLaunches = userDefault->getIntegerForKey("APPLAUNCH1", 0);
    if(appLaunches == 0)
    {
        showHelpText("Drag solid circle to eat hollows");
    }
    else
    {
        //no need of slicer when particles are updated
        addSlicer();
    }
    userDefault->setIntegerForKey("APPLAUNCH1", appLaunches + 1);
    
    //addKillerCircle();
    this->scheduleUpdate();
    this->addChild(levelLabel,3);
    this->addChild(levelScoreBar,3);
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
            auto scene = GameOverScreen::createScene(level, GameScreen::numtry);
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
                auto scene = GameOverScreen::createScene(level,GameScreen::numtry);
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
        if(level % 10 == 0)
        {
            colorIndex = (colorIndex + 1 ) % BGColors;
        }
        Color3B c = Color3B(u.getBgColor(colorIndex).r,u.getBgColor(colorIndex).g,u.getBgColor(colorIndex).b);
        layerColor->setColor(c);
        int numKC = u.getNumKillerCircles(level) - u.getNumKillerCircles(level -1);
        for(int i=0; i < numKC; ++i)
        {
            addKillerCircle();
        }
    }
    levelLabel->setText(u.scoreAsStr(level));
    float percent = score/(float)u.getLevelScoreNeeded(level);
    percent = percent * 100;
    //CCLOG("percent %f , score %d, fromLevel %d",percent,score, u.getLevelScoreNeeded(level) );
    levelScoreBar->setPercent(percent);

}

void GameScreen::showHelpText(std::string msg)
{
    helpLabel = ui::Text::create(msg, "courier.ttf", 64);
    helpLabel->setScale(0.95*winSize.width/(helpLabel->getContentSize().width));
    helpLabel->setAnchorPoint(Vec2(0.5f,1.0f));
    helpLabel->setPosition(Vec2(winSize.width/2, winSize.height - winSize.height/100 - 4));
    helpLabel->setColor(Color3B(255,255,255));
    helpLabel->setOpacity(0.0f);
    this->addChild(helpLabel,3);
    
    auto fadeIn = FadeIn::create(1.0f);
    auto fadeOut = FadeOut::create(1.0f);
    auto delay = DelayTime::create(2.0f);
    
    auto hitOnlyWhite = CallFunc::create([&](){
        changeText("Don't hit on black things.");
    });
    
    auto tapSize = CallFunc::create([&](){
        changeText("Tap solid cirlce to reduce size.");
    });
    
    auto newThings = CallFunc::create([&](){
        changeText("Watch out for new objects.");
    });
    
    auto addSlicerCall = CallFunc::create([&](){
        addSlicer();
    });


    
    auto seq = Sequence::create(fadeIn, delay, fadeOut,
                                hitOnlyWhite, fadeIn, delay, fadeOut,
                                tapSize,      fadeIn, delay, fadeOut,
                                newThings,    fadeIn, delay, fadeOut,
                                addSlicerCall, nullptr);
    helpLabel->runAction(seq);

}

void GameScreen::changeText(std::string msg)
{
    helpLabel->setText(msg);
    helpLabel->setScale(0.95*winSize.width/(helpLabel->getContentSize().width));
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

void GameScreen::setKillerCircles()
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
    spot->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(spot,2);
}

