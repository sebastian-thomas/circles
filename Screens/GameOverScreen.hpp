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
#include "PluginFacebook/PluginFacebook.h"

class GameOverScreen : public cocos2d::Layer, sdkbox::FacebookListener
{
    static int score;
    static int numtried;
    
public:
    static cocos2d::Scene* createScene(int s, int numtried);
    virtual bool init();
    
    CREATE_FUNC(GameOverScreen);
    void setScore(int s);
    
private:
    void startGame(cocos2d::CCObject* pSender);
    void continueGame();
    void inviteFbFriend(cocos2d::CCObject* pSender);
    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
    
    
    void onLogin(bool isLogin, const std::string& msg);
    void onSharedSuccess(const std::string& message);
    void onSharedFailed(const std::string& message);
    void onSharedCancel();
    void onAPI(const std::string& key, const std::string& jsonData);
    void onPermission(bool isLogin, const std::string& msg);
    void onFetchFriends(bool ok, const std::string& msg);
    void onRequestInvitableFriends( const sdkbox::FBInvitableFriendsInfo& friends );
    void onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg );
    void onInviteFriendsResult( bool result, const std::string& msg );
    void onGetUserInfo( const sdkbox::FBGraphUser& userInfo );
};
#endif /* GameOverScreen_hpp */
