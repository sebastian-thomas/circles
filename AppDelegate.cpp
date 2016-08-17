#include "AppDelegate.h"
#include "Definitions.h"
#include "HelloWorldScene.h"
#include "Screens/GameScreen.h"
#include "Screens/MenuScreen.hpp"

#include "PluginFacebook/PluginFacebook.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    sdkbox::PluginFacebook::init();
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
            glview = GLViewImpl::createWithRect("Hello World", Rect(0,0, 480, 640));
        #else
            glview = GLViewImpl::create("Hello World");
        #endif
        //glview = GLViewImpl::create("Hello World");
       // glview->setFrameSize(480, 640);
        director->setOpenGLView(glview);
        //glview->setDesignResolutionSize(APP_WIDTH, APP_HEIGHT, kResolutionFixedHeight);
    }
    
    //auto scene = GameScreen::createScene();
    auto scene = MenuScreen::createScene();
    director->runWithScene(scene);
    
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}