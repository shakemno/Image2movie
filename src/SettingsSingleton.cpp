//
//  SettingsSingleton.cpp
//  Image2movie
//
//  Created by shakemno on 7/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "SettingsSingleton.h"


SettingsSingleton* SettingsSingleton::getInstance() 
{
    static SettingsSingleton theInstance;
    return &theInstance;
}

void SettingsSingleton::setWidth(int w)
{
    width = w;
};

void SettingsSingleton::setHeight(int h)
{
    height = h;
};

void SettingsSingleton::setNormalTime(int t)
{
    normalTime = t;    
};

void SettingsSingleton::setSpecialTime(int ts)
{
    specialTime = ts;    
};

int SettingsSingleton::getWidth()
{
    return width;
};

int SettingsSingleton::getHeight()
{
    return height;
};

int SettingsSingleton::getNormalTime()
{
    return normalTime;
};

int SettingsSingleton::getSpecialTime()
{
    return specialTime;
};