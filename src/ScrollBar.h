//
//  ScrollBar.h
//  Image2movie
//
//  Created by shakemno on 7/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Image2movie_ScrollBar_h
#define Image2movie_ScrollBar_h

#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"

class ScrollBar : public ofxMSAInteractiveObject
{
    int mWidth, bgHeight, barHeight, mx, my;
    float scrollHeight, scrollMax;
    
public:
    ScrollBar(int _w, int _bgH, _x, _y, _max)
    {
        mWidth = _w;
        bgHeight = _bgH;
        mx = _x;
        my = _y;
        scrollMax = _max;
        
        scrollHeight = (ofGetHeight()/mScrollMax)*sH;
    }
    
	void onRollOver(int x, int y)
    {
    }
    
    void onRollOut()
    {
    }
    
    void onMouseMove(int x, int y)					
    {
    }
    
    void onDragOver(int x, int y, int button)		
    {
    }
    
    void onDragOutside(int x, int y, int button)	
    {
    }
    
    void onPress(int x, int y, int button)			
    {
    }
    
    void onRelease(int x, int y, int button)		
    {
    }
    
    void onReleaseOutside(int x, int y, int button)	
    {
    }
    
    void update()
    {
    
    }
    
    void draw()
    {
        ofSetColor(0);
        ofRect(0,0, mWidth, bgHeight);
        
        ofSetColor(255);
        ofRect()
    
    }
};

#endif
