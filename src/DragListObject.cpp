//
//  DragListObject.cpp
//  Image2movie
//
//  Created by shakemno on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DragListObject.h"

#define DEF_COL 150
#define OVER_COL 100

#define DEF_COL_SEL 230
#define OVER_COL_SEL 180

DragListObject::DragListObject(string _name, string _imgPath, int _y, float _w)
{
    y = _y;
    orgY = _y;
    w = _w;
    
    int maxLen = 25;
    name = (_name.length()>maxLen) ? _name.substr(0,maxLen)+"..." : _name;
    
    //img.setUseTexture(true);
    //if(y < ofGetHeight()-100) img.loadImage(_imgPath);
    
    path = _imgPath;
    
    isExtra = false;
    
    overColor.set(DEF_COL);
}

void DragListObject::draw()
{
    ofSetColor(overColor);
    ofRect(0, 0, w, 30);
    
    ofSetColor(255);
    if(img.isAllocated())img.draw(0,0);    
    
    ofDrawBitmapString(name, 40, 20);
}

void DragListObject::onRelease(int x, int y, int button)
{
    isExtra = !isExtra;
    
    if(isExtra) overColor.set(OVER_COL_SEL);
    else overColor.set(OVER_COL);
}

void DragListObject::onRollOver(int x, int y) {
//    printf("MyTestObject::onRollOver(x: %i, y: %i)\n", x, y);
    
    if(isExtra) overColor.set(OVER_COL_SEL);
    else overColor.set(OVER_COL);
    
    this->setImage();
}

void DragListObject::onRollOut() {
//    printf("MyTestObject::onRollOut()\n");

    if(isExtra) overColor.set(DEF_COL_SEL);
    else overColor.set(DEF_COL);
    
}

void DragListObject::disableMouseEvents() 
{
    if(isExtra) overColor.set(DEF_COL_SEL);
    else overColor.set(DEF_COL);
    
    ofxObject::disableMouseEvents();
}

void DragListObject::setImage()
{
//    cout << img.isAllocated() << endl;
    if(!img.isAllocated())
    {
        img.setImageType(OF_IMAGE_COLOR);
        img.loadImage(path);
        img.resize(30, 30);  
    
    }
}