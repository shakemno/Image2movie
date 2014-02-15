//
//  SettingsSingleton.h
//  Image2movie
//
//  Created by shakemno on 7/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Image2movie_SettingsSingleton_h
#define Image2movie_SettingsSingleton_h
#include "ofMain.h"

struct dragObj
{
    string path;
    bool isExtra;
};

class SettingsSingleton
{
    
    private:
        SettingsSingleton(void)	{ printf("SettingsSingleton "); }
        ~SettingsSingleton(void){ printf("~SettingsSingleton "); }
    
        int width, height, normalTime, specialTime;
    
    public:
        void setWidth(int w);
        void setHeight(int h);
        void setNormalTime(int t);
        void setSpecialTime(int ts);
        int getWidth();
        int getHeight();
        int getNormalTime();
        int getSpecialTime();
        static SettingsSingleton *getInstance();        
};

#endif
