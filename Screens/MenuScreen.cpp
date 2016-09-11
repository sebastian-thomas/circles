//
//  MenuScreen.cpp
//  OTap
//
//  Created by Sebastian on 17/07/16.
//
//

#include "MenuScreen.hpp"
#include "cocos2d.h"

#include "Definitions.h"
#include "GameScreen.h"
#include "ui/CocosGUI.h"
#include "../OUtility.h"

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
    OUtility u;
    
    this->setKeyboardEnabled(true);
    
    auto layerColor = new LayerColor;
    layerColor->initWithColor(u.getBgColor(RandomHelper::random_int(0,BGColors-1)));
    //layerColor->initWithColor(u.getBgColor(0));
    this->addChild(layerColor, 1);
    
    Vector<MenuItem*> menuItems;

    
    auto playItem = MenuItemImage::create("play-button.png", "play-button.png",
                                          CC_CALLBACK_1(MenuScreen::startGame, this));
    //playItem->setContentSize(Size(winSize.width/3,winSize.width/3));
    playItem->setScale(winSize.width/(4*playItem->getContentSize().width));
    playItem->setAnchorPoint(Vec2(0.5f,0.0f));
    playItem->setPosition(winSize.width/2, winSize.height/4);
    menuItems.pushBack(playItem);
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu,2);
    
    auto nameLabel = ui::Text::create("Circles", "Circular Abstracts.ttf", 124);
    nameLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
    nameLabel->setAnchorPoint(Vec2(0.5f,0.5f));
    nameLabel->setScale(3*winSize.width/(nameLabel->getContentSize().width * 4));
    nameLabel->setPosition(Vec2(winSize.width/2,0.75*winSize.height));
    nameLabel->setColor(Color3B(255,255,255));
    
    auto myAppLabel = ui::Text::create(".myAppStack()", "courier.ttf", 124);
    myAppLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
    myAppLabel->setAnchorPoint(Vec2(0.5f,0.0f));
    myAppLabel->setScale(winSize.width/(myAppLabel->getContentSize().width * 5));
    myAppLabel->setPosition(Vec2(winSize.width/2,0));
    myAppLabel->setColor(Color3B(255,255,255));
    
    this->addChild(nameLabel,2);
    this->addChild(myAppLabel,2);
    
    return true;
}

void MenuScreen::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    Director::getInstance()->end();
}

void MenuScreen::startGame(CCObject* pSender)
{
    auto scene = GameScreen::createScene(1,0);
    Director::getInstance()->replaceScene(scene);
}