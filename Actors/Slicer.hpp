//
//  Slicer.hpp
//  OTap
//
//  Created by Sebastian on 16/07/16.
//
//

#ifndef Slicer_hpp
#define Slicer_hpp

#include "cocos2d.h"


class Slicer : public cocos2d::Sprite
{
public:
    Slicer();
    ~Slicer();
    
    static Slicer *create(int type);
    int getRadius();
    
    bool isOutOfScreen();
    void spawnSlicer();
    
private:
    int type;
    int speed;
    
    cocos2d::Vec2 winSize;
    int minSize, maxSize;
    int r;
    
    void initWithOptions(int type);
    int getDist(int x1,int y1, int x2, int y2);
};


#endif /* Slicer_hpp */
