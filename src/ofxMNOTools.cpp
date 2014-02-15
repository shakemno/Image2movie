//
//  ofxMNOTools.cpp
//  HoldTheLineExhibition
//
//  Created by shakemno on 5/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofxMNOTools.h"


void ofxMNOTools::fixStringEncoding(string &_orig)
{
    for (int i=0; i < 56; i++) 
    { 
        while (_orig.find(chars[i].character) != string::npos) 
        {
            _orig = _orig.substr(0, _orig.find(chars[i].character)) + chars[i].code + _orig.substr(_orig.find(chars[i].character) + 2);
        }
    }
};

ofRectangle ofxMNOTools::scaleToFitKeepRatio(float orgWidth, float orgHeight)
{
    float ImgRatio = orgWidth / orgHeight;
    
    if (orgWidth < ofGetWidth() || orgWidth > ofGetWidth())
    {
        orgWidth = ofGetWidth();
        orgHeight = orgWidth/ImgRatio;
    }
    
    if (orgHeight > ofGetHeight())
    {
        orgHeight = ofGetHeight();
        orgWidth = orgHeight*ImgRatio;
    }
    
    float sx = ofGetWidth()/2 - orgWidth/2;
    float sy = ofGetHeight()/2 - orgHeight/2;
    
    return ofRectangle(sx, sy, orgWidth, orgHeight);
};

ofRectangle ofxMNOTools::scaleToFitKeepRatio(float orgWidth, float orgHeight, float toFitWidth, float toFitHeight)
{
    float ImgRatio = orgWidth / orgHeight;
    
    if (orgWidth < toFitWidth || orgWidth > toFitWidth)
    {
        orgWidth = toFitWidth;
        orgHeight = orgWidth/ImgRatio;
    }
    
    if (orgHeight > toFitHeight)
    {
        orgHeight = toFitHeight;
        orgWidth = orgHeight*ImgRatio;
    }
    
    float sx = toFitWidth/2 - orgWidth/2;
    float sy = toFitHeight/2 - orgHeight/2;
    
    return ofRectangle(sx, sy, orgWidth, orgHeight);
};

ofRectangle ofxMNOTools::scaleToFillKeepRatio(float orgWidth, float orgHeight)
{
    float ImgRatio = orgWidth / orgHeight;
    
    if (orgWidth < ofGetWidth())
    {
        orgWidth = ofGetWidth();
        orgHeight = orgWidth/ImgRatio;
    }
    
    if (orgHeight < ofGetHeight())
    {
        orgHeight = ofGetHeight();
        orgWidth = orgHeight*ImgRatio;
    }
    
    float sx = ofGetWidth()/2 - orgWidth/2;
    float sy = ofGetHeight()/2 - orgHeight/2;
    
    return ofRectangle(sx, sy, orgWidth, orgHeight);
};


//rounded rect
void ofxMNOTools::roundedRect(float x, float y, float w, float h, float r) 
{
    ofBeginShape();
    ofVertex(x+r, y);
    ofVertex(x+w-r, y);
    quadraticBezierVertex(x+w, y, x+w, y+r, x+w-r, y);
    ofVertex(x+w, y+h-r);
    quadraticBezierVertex(x+w, y+h, x+w-r, y+h, x+w, y+h-r);
    ofVertex(x+r, y+h);
    quadraticBezierVertex(x, y+h, x, y+h-r, x+r, y+h);
    ofVertex(x, y+r);
    quadraticBezierVertex(x, y, x+r, y, x, y+r);
    ofEndShape();
}

void ofxMNOTools::quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY) 
{
    float cp1x = prevX + 2.0/3.0*(cpx - prevX);
    float cp1y = prevY + 2.0/3.0*(cpy - prevY);
    float cp2x = cp1x + (x - prevX)/3.0;
    float cp2y = cp1y + (y - prevY)/3.0;
    
    // finally call cubic Bezier curve function
    ofBezierVertex(cp1x, cp1y, cp2x, cp2y, x, y);
};




