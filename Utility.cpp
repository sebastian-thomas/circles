//
//  Utility.cpp
//  OTap
//
//  Created by Sebastian on 27/07/16.
//
//

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Utility
{
    Color4B bgColors[BGColors];
    
    
public:
    static int menuBgColor;
    
    Utility()
    {
        initBgColors();
    }
    
    void initBgColors()
    {
        bgColors[0] = Color4B(70,  32, 102, 255);
        bgColors[1] = Color4B(255,  122, 90, 255);
        bgColors[2] = Color4B(0,  170, 160, 255);
    }
    
    
    Color4B getBgColor(int i)
    {
        if(i >=0 && i < BGColors) {
            return bgColors[i];
        }
        else {
            return bgColors[0];
        }
    }
};

