//
//  Particle.hpp
//  OTap
//
//  Created by Sebastian on 02/07/16.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include "cocos2d.h"


class Particle : public cocos2d::Sprite
{
public:
    Particle();
    ~Particle();
    
    static Particle *create();
    int getRadius();
    
private:
    cocos2d::Vec2 winSize;
    int minSize, maxSize;
    int r;
    
    void initWithOptions();
};

#endif /* Particle_hpp */
