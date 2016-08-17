//
//  Utility.cpp
//  OTap
//
//  Created by Sebastian on 27/07/16.
//
//

#include "cocos2d.h"
#include "Definitions.h"
#include "OUtility.h";

USING_NS_CC;

OUtility::OUtility()
{
    initBgColors();
}

int OUtility::getNumKillerCircles(int level)
{
    int lvl = level / 10;
    if (lvl > NUMLEVEL-1 || lvl < 0)
    {
        return numKillerCircles[NUMLEVEL-1];
    }
    else
    {
        return numKillerCircles[lvl];
    }
}

int OUtility::getLevelScoreNeeded(int level)
{
    int lvl = level / 10;
    if (lvl > NUMLEVEL-1 || lvl < 0)
    {
        return levelScores[NUMLEVEL-1];
    }
    else
    {
        return levelScores[lvl];
    }
}

void OUtility::initBgColors()
{
    bgColors[0] = Color4B(255,  122, 90, 255);
    bgColors[1] = Color4B(0,  170, 160, 255);
    bgColors[2] = Color4B(201,  0, 93, 255);
    bgColors[3] = Color4B(255,  191, 0, 255);
    bgColors[4] = Color4B(251,  115, 116, 255);
    bgColors[5] = Color4B(163,  27, 196, 255);
}


Color4B OUtility::getBgColor(int i)
{
    if(i >=0 && i < BGColors) {
        return bgColors[i];
    }
    else {
        return bgColors[0];
    }
}

std::string OUtility::scoreAsStr(int val)
{
    std::ostringstream os ;
    os << val ;
    return os.str() ;
}
