//
//  ExportMovieThread.h
//  Image2movie
//
//  Created by shakemno on 7/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Image2movie_ExportMovieThread_h
#define Image2movie_ExportMovieThread_h

#include "ofxQTVideoSaver.h"
#include "DragListObject.h"

class ExportMovieThread : public ofThread
{
    ofxQtVideoSaver *mVidSaver;
    int w, h;
    vector <string> dragList;
    
public:
    
    //use pointer
//    ExportMovieThread(int _w, int _h, string filename, vector <DragListObject> *_dragList)
    ExportMovieThread(int _w, int _h, string filename, vector <string> _dragList)
    {
        cout << "enter thread" << endl;
        w = _w;
        h = _h;
        
        dragList = _dragList;
        
        // init the movie saver
        mVidSaver = new ofxQtVideoSaver();
        mVidSaver->setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_HIGH);
        mVidSaver->setup(w, h, filename);   
        
        cout << "list size " << dragList.size() << endl;
    }
    
    ~ExportMovieThread()
    {
        cout << "delete thread" << endl;
        delete mVidSaver;
    }
    
    void start()
    {
        startThread(true, false);   // blocking, verbose
    }
    
    void stop()
    {
        stopThread();
    }
    
    //--------------------------
    //only this cant handle gl-calls - draw in function and only load images here?!
    void threadedFunction()
    {
        lock();
        
        cout << "enter threadedFunction" << endl;          
        cout << "threadedFunction size " << dragList.size() << endl;
        
        ofImage *pixImg;
        
        //sanity check if is recording
        for (int i = 0; i < dragList.size(); i++) 
        {
            pixImg = new ofImage();
            pixImg->setUseTexture(false);
            pixImg->allocate(w, h, OF_IMAGE_COLOR);
            pixImg->loadImage(dragList[i]);
            pixImg->resize(w, h);
            
            mVidSaver->addFrame(pixImg->getPixels(), 0.5);        
            
            delete pixImg;
        }
        
        mVidSaver->finishMovie(); 
        
        unlock();
    }   
    
    void update() 
    {
        cout << "test" << endl;
    };
    
    void draw() {};
};

#endif
