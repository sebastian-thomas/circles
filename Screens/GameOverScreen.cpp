//
//  GameOverScreen.cpp
//  OTap
//
//  Created by Sebastian on 30/07/16.
//
//
#include "GameOverScreen.hpp"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "GameScreen.h"
#include "../Definitions.h"
#include "../OUtility.h"

USING_NS_CC;

int GameOverScreen::score;

Scene* GameOverScreen::createScene(int s)
{
    // 'scene' is an autorelease object
    GameOverScreen::score = s;
    auto scene = Scene::create();
    auto layer = GameOverScreen::create();
    scene->addChild(layer);
    CCLOG("Score from create scene : %d",s);
    return scene;
}

bool GameOverScreen::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    OUtility u;
    
    this->setKeyboardEnabled(true);
    
    UserDefault *userDefault = UserDefault::getInstance();
    //reset high score
    //userDefault->setIntegerForKey("HIGHSCORE", 0);
    auto highScore = userDefault->getIntegerForKey("HIGHSCORE", 0);
    if(GameOverScreen::score > highScore)
    {
        highScore = GameOverScreen::score;
        userDefault->setIntegerForKey("HIGHSCORE", highScore);
    }
    
    auto layerColor = new LayerColor;
    layerColor->initWithColor(u.getBgColor(RandomHelper::random_int(0,BGColors-1)));
    this->addChild(layerColor, 1);
    
    Vector<MenuItem*> menuItems;

    
    auto playItem = MenuItemImage::create("replay.png", "replay.png",
                                          CC_CALLBACK_1(GameOverScreen::startGame, this));
    //playItem->setContentSize(Size(winSize.width/3,winSize.width/3));
    playItem->setScale(winSize.width/(3*playItem->getContentSize().width));
    playItem->setAnchorPoint(Vec2(0.5f,0.5f));
    playItem->setPosition(winSize.width/2, winSize.height/3);
    menuItems.pushBack(playItem);
    
    auto scoreLabel = ui::Text::create(u.scoreAsStr(GameOverScreen::score), "Circular Abstracts.ttf", 248);
    scoreLabel->setAnchorPoint(Vec2(0.5f,0.5f));
    //scoreLabel->setScale(winSize.width/(scoreLabel->getContentSize().width * 3));
    scoreLabel->setScale(winSize.height/(scoreLabel->getContentSize().height * 4));
    //scoreLabel->setScale(winSize.width/(scoreLabel->getContentSize().width * 3),
     //                                   winSize.height/(scoreLabel->getContentSize().height * 4));
    scoreLabel->setPosition(Vec2(winSize.width/2,0.75*winSize.height));
    scoreLabel->setColor(Color3B(255,255,255));
    
    auto highScoreLabel = ui::Text::create("HIGHEST : " +u.scoreAsStr(highScore), "Circular Abstracts.ttf", 124);
    highScoreLabel->setAnchorPoint(Vec2(0.5f,1.0f));
    highScoreLabel->setScale(winSize.width/(highScoreLabel->getContentSize().width * 3));
    highScoreLabel->setPosition(Vec2(winSize.width/2, 0.75*winSize.height - 0.2*winSize.height));
    highScoreLabel->setColor(Color3B(255,255,255));
    
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2(0,0));
    
    this->addChild(menu,2);
    this->addChild(scoreLabel,2);
    this->addChild(highScoreLabel,2);
    return true;
}

void GameOverScreen::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    Director::getInstance()->end();
}

void GameOverScreen::startGame(CCObject* pSender)
{
    auto scene = GameScreen::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameOverScreen::setScore(int s)
{
    score = s;
}