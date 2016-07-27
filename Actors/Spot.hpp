//
//  Spot.hpp
//  OTap
//
//  Created by Sebastian on 02/07/16.
//
//

#ifndef Spot_hpp
#define Spot_hpp

#include "cocos2d.h"

class Spot : public cocos2d::Sprite
{
public:
    Spot();
    ~Spot();
    static Spot* create(cocos2d::String fname);
    
    //GamePlay
    void addArea(int r);
    void reduceSize();
    
private:
    int defSize;
    int currSize;
    cocos2d::Vec2 winSize;
    bool swiped;

    
    void setToRadius(int r);
    void initOptions();
    void addEvents();
    
    
    //handling touches
    cocos2d::Point touchOffset;
    cocos2d::Point touchToPoint(cocos2d::Touch* touch);
    bool isTouchingSpot(cocos2d::Touch* touch);
    //multi touch enabled
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    cocos2d::Point getInScreenPoint(cocos2d::Point p);
    
};

#endif /* Spot_hpp */
