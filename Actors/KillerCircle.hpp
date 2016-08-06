//
//  KillerCircle.hpp
//  OTap
//
//  Created by Sebastian on 03/08/16.
//
//

#ifndef KillerCircle_hpp
#define KillerCircle_hpp


#include "cocos2d.h"


class KillerCircle : public cocos2d::Sprite
{
public:
    KillerCircle();
    ~KillerCircle();
    
    static KillerCircle *create();
    int getRadius();
    
    bool isOutOfScreen();
    void spawnKillerCircle(int sz);
    bool isWhite();
    
private:
    
    bool isWhiteSprite;
    cocos2d::Sprite *innerSprite;
    
    cocos2d::Vec2 winSize;
    int minSize, maxSize;
    int r;
    
    
    void initWithOptions();
    void toggleCircle(int initalSize);
    int getDist(int x1,int y1, int x2, int y2);
};


#endif /* KillerCircle_hpp */
