//
//  MenuScreen.hpp
//  OTap
//
//  Created by Sebastian on 17/07/16.
//
//

#ifndef MenuScreen_hpp
#define MenuScreen_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MenuScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MenuScreen);
    
private:
    void startGame(cocos2d::CCObject* pSender);
};

#endif /* MenuScreen_hpp */
