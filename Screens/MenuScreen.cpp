//
//  MenuScreen.cpp
//  OTap
//
//  Created by Sebastian on 17/07/16.
//
//

#include "MenuScreen.hpp"
#include "GameScreen.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "../Utility.cpp"

USING_NS_CC;

Scene* MenuScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = MenuScreen::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MenuScreen::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    Utility u;
    
    auto layerColor = new LayerColor;
    layerColor->initWithColor(u.getBgColor(RandomHelper::random_int(0,BGColors-1)));
    this->addChild(layerColor, 1);
    
    auto label = Label::createWithSystemFont("otap", "Arial", 96);
    label->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    label->setPosition(winSize.width/2, winSize.height*0.75);
    this->addChild(label, 2);
    
   
    
    auto play = Label::createWithSystemFont("play", "Arial", 96);
    play->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    play->setPosition(winSize.width/2, winSize.height*0.25);
    //this->addChild(play, 2);
    
    
    Vector<MenuItem*> menuItems;
    
    auto playItem = MenuItemImage::create("play-button.png", "play-button.png",
                                          CC_CALLBACK_1(MenuScreen::startGame, this));
    //playItem->setContentSize(Size(winSize.width/3,winSize.width/3));
    playItem->setScale(winSize.width/(4*playItem->getContentSize().width));
    playItem->setAnchorPoint(Vec2(0.5f,0.5f));
    playItem->setPosition(winSize.width/2, winSize.height/4);
    menuItems.pushBack(playItem);
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu,2);
    return true;
}

void MenuScreen::startGame(CCObject* pSender)
{
    auto scene = GameScreen::createScene();
    Director::getInstance()->replaceScene(scene);
}