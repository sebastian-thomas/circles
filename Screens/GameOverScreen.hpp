//
//  GameOverScreen.hpp
//  OTap
//
//  Created by Sebastian on 30/07/16.
//
//

#ifndef GameOverScreen_hpp
#define GameOverScreen_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOverScreen : public cocos2d::Layer
{
    static int score;
    
public:
    static cocos2d::Scene* createScene(int s);
    virtual bool init();
    
    CREATE_FUNC(GameOverScreen);
    void setScore(int s);
    
private:
    void startGame(cocos2d::CCObject* pSender);
    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
};
#endif /* GameOverScreen_hpp */
