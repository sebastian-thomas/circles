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

#include "PluginFacebook/PluginFacebook.h"

USING_NS_CC;

int GameOverScreen::score;
int GameOverScreen::numtried;

Scene* GameOverScreen::createScene(int s, int numtried)
{
    // 'scene' is an autorelease object
    GameOverScreen::score = s;
    GameOverScreen::numtried = numtried;
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
    
    sdkbox::PluginFacebook::setListener(this);
    
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
    //layerColor->initWithColor(u.getBgColor(RandomHelper::random_int(0,BGColors-1)));
    layerColor->initWithColor(Color4B(94,  94, 94, 255));
    this->addChild(layerColor, 1);
    
    Vector<MenuItem*> menuItems;

    
    auto playItem = MenuItemImage::create("replay.png", "replay.png",
                                          CC_CALLBACK_1(GameOverScreen::startGame, this));
    //playItem->setContentSize(Size(winSize.width/3,winSize.width/3));
    playItem->setScale(winSize.width/(4*playItem->getContentSize().width));
    playItem->setAnchorPoint(Vec2(0.5f,0.5f));
    
    
    auto fbReplayItem = MenuItemImage::create("replayfb.png", "replayfb.png",
                                          CC_CALLBACK_1(GameOverScreen::inviteFbFriend, this));
    //playItem->setContentSize(Size(winSize.width/3,winSize.width/3));
    fbReplayItem->setScale(winSize.width/(4*playItem->getContentSize().width));
    fbReplayItem->setAnchorPoint(Vec2(0.5f,0.5f));
    fbReplayItem->setPosition(winSize.width*0.75, winSize.height/3);
    
    if ( GameOverScreen::numtried > 1)
    {
        playItem->setPosition(winSize.width*0.5, winSize.height/3);
        menuItems.pushBack(playItem);
    }
    else
    {
        playItem->setPosition(winSize.width*0.25, winSize.height/3);
        menuItems.pushBack(playItem);
        menuItems.pushBack(fbReplayItem);
    }
    
    
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
    
    auto reviveFBLabel = ui::Text::create("Invite a friend and Revive", "Circular Abstracts.ttf", 124);
    reviveFBLabel->setAnchorPoint(Vec2(0.5f,1.0f));
    reviveFBLabel->setScale(winSize.width/(reviveFBLabel->getContentSize().width * 3));
    reviveFBLabel->setPosition(Vec2(winSize.width/2, 0.25*winSize.height));
    reviveFBLabel->setColor(Color3B(255,255,255));
    reviveFBLabel->addTouchEventListener(CC_CALLBACK_1(GameOverScreen::inviteFbFriend, this));
    
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2(0,0));
    
    this->addChild(menu,2);
    this->addChild(scoreLabel,2);
    this->addChild(highScoreLabel,2);
    //this->addChild(reviveFBLabel,2);
    return true;
}

void GameOverScreen::inviteFbFriend(CCObject* pSender)
{
    CCLOG("invite fiend");
    //auto scene = GameScreen::createScene(GameOverScreen::numtried + 1);
    //Director::getInstance()->replaceScene(scene);
    
    if(!sdkbox::PluginFacebook::isLoggedIn())
    {
        sdkbox::PluginFacebook::login();
        sdkbox::PluginFacebook::requestReadPermissions({sdkbox::FB_PERM_READ_PUBLIC_PROFILE, sdkbox::FB_PERM_READ_USER_FRIENDS});

    }
    else{
        sdkbox::PluginFacebook::inviteFriends(
                                              "https://fb.me/1783355538608915",
                                              "http://myappstack.com/img/circles/fg.png");
         
        //auto scene = GameScreen::createScene(GameOverScreen::numtried + 1, score);
        //Director::getInstance()->replaceScene(scene);
         
        //sdkbox::PluginFacebook::logout();
    }
}

void GameOverScreen::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    Director::getInstance()->end();
}

void GameOverScreen::startGame(CCObject* pSender)
{
    auto scene = GameScreen::createScene(1,0);
    Director::getInstance()->replaceScene(scene);
}

void GameOverScreen::continueGame()
{
    auto scene = GameScreen::createScene(GameOverScreen::numtried + 1, GameOverScreen::score);
    Director::getInstance()->replaceScene(scene);
}

void GameOverScreen::setScore(int s)
{
    score = s;
}

void GameOverScreen::onLogin(bool isLogin, const std::string& msg)
{
    sdkbox::PluginFacebook::inviteFriends(
                                          "https://fb.me/1783355538608915",
                                          "http://myappstack.com/img/circles/fg.png");
}
void GameOverScreen::onSharedSuccess(const std::string& message){}
void GameOverScreen::onSharedFailed(const std::string& message){}
void GameOverScreen::onSharedCancel(){}
void GameOverScreen::onAPI(const std::string& key, const std::string& jsonData){}
void GameOverScreen::onPermission(bool isLogin, const std::string& msg){}
void GameOverScreen::onFetchFriends(bool ok, const std::string& msg){}
void GameOverScreen::onRequestInvitableFriends( const sdkbox::FBInvitableFriendsInfo& friends ){}
void GameOverScreen::onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg ){}
void GameOverScreen::onInviteFriendsResult( bool result, const std::string& msg )
{
    CCLOG(" on invite friend result aah %d", result);
    if(result)
    {
        auto callbackContinue = CallFunc::create([this](){
            continueGame();
        });
        auto delay = DelayTime::create(1.0f);
        auto sequence = Sequence::create( delay,callbackContinue,nullptr);
        this->runAction(sequence);
    }
    
}
void GameOverScreen::onGetUserInfo( const sdkbox::FBGraphUser& userInfo ){}