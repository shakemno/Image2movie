//
//  DragListObject.h
//  Image2movie
//
//  Created by shakemno on 7/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxObject.h"

class DragListObject : public ofxObject
{
private:
    string name;
//    ofImage img;
    ofColor overColor;
    
    void setImage();
    
public:
    DragListObject(string _name, string _imgPath, int _y, float _w);
    
    //should all be private...!
    string path;
    ofImage img;
    int y, orgY;
    float w;
    bool isExtra;
    
    void draw();
    void onRelease(int x, int y, int button);
    void onRollOver(int x, int y);
	void onRollOut();
    
    void disableMouseEvents();
};
