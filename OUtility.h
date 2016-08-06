//
//  OUtility.h
//  OTap
//
//  Created by Sebastian on 30/07/16.
//
//

#ifndef OUtility_h
#define OUtility_h

#include "cocos2d.h"
#include "Definitions.h"

class OUtility
{
    cocos2d::Color4B bgColors[BGColors];
    
    //powerup and level management
    int levelScores[NUMLEVEL]      = {10, 10, 10, 20, 20, 20, 20, 20, 30, 40};
    int numKillerCircles[NUMLEVEL] = { 0, 1,  1,  2,  2,  2,  2,  3,  3,  4 };
public:

    OUtility();
    
    int getLevelScoreNeeded(int level);
    int getNumKillerCircles(int level);
    
    
    void initBgColors();
    cocos2d::Color4B getBgColor(int i);
    std::string scoreAsStr(int val);
};



#endif /* OUtility_h */
