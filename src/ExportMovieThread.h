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
#include "ofxMNOTools.h"
#include "SettingsSingleton.h"

#define FADE_TIME 30

class ExportMovieThread : public ofThread
{  
    ofxQtVideoSaver *mVidSaver;
    int w, h, imgCounter, normalTime, specialTime;
    vector <dragObj> dragList;
    
    ofFbo *mfbo;
    ofPixels pix;
    
    float mw, mh;
    ofRectangle p1, p2;
    ofImage *img1;
    ofImage *img2;
    int alpha1;
    
    bool loadImg, drawOnce;
    
    ofTrueTypeFont ttf;
    
public:
    
    ExportMovieThread(ofFbo *fbo, string filename, vector <dragObj> _dragList)
    {
        loadImg = true;
        drawOnce = true;
        imgCounter = 0;
        
        SettingsSingleton *s = SettingsSingleton::getInstance();
        
        w = s->getWidth();
        h = s->getHeight();
        
        normalTime = s->getNormalTime();
        specialTime = s->getSpecialTime();
        
        mfbo = fbo;
        
        dragList = _dragList;
        
        // init the movie saver
        mVidSaver = new ofxQtVideoSaver();
        mVidSaver->setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_HIGH);
        mVidSaver->setup(w, h, filename);   
        
        ofAddListener(ofEvents().update, this, &ExportMovieThread::_update);
        ofAddListener(ofEvents().draw, this, &ExportMovieThread::_draw);
        
        ttf.loadFont("GUI/NewMedia Fett.ttf", 12);
    }
    
    ~ExportMovieThread()
    {
        delete img1, img2;
        delete mVidSaver;
    }
    
    void start()
    {
        startThread(true, true);   // blocking, verbose
    }
    
    void stop()
    {
        ofRemoveListener(ofEvents().update, this, &ExportMovieThread::_update);
        ofRemoveListener(ofEvents().draw, this, &ExportMovieThread::_draw);
        stopThread();
    }
    
    //--------------------------
    //only this cant handle gl-calls - draw in function and only load images here?!
    void threadedFunction()
    {        
        while(isThreadRunning())
        {
            if(loadImg)
            {
                //make one image load function… so much repeating code
                if(imgCounter == 0)
                {
                    img1 = new ofImage();
                    img1->setUseTexture(false);
                    img1->setImageType(OF_IMAGE_COLOR);
                    img1->loadImage(dragList[imgCounter].path);
                    mw = (float) img1->width;
                    mh = (float) img1->height;
                    p1 = ofxMNOTools::scaleToFitKeepRatio(mw, mh, mfbo->getWidth(), mfbo->getHeight());
                    img1->resize(p1.width,p1.height);
                    
                    imgCounter++;
                    
                    img2 = new ofImage();
                    img2->setUseTexture(false);
                    img2->setImageType(OF_IMAGE_COLOR);
                    img2->loadImage(dragList[imgCounter].path);
                    mw = (float) img2->width;
                    mh = (float) img2->height;
                    p2 = ofxMNOTools::scaleToFitKeepRatio(mw, mh, mfbo->getWidth(), mfbo->getHeight());
                    img2->resize(p2.width,p2.height);
                }
                else
                {
                    //not very nice, but opengl texture breaks thread… find solution?!
                    img1 = new ofImage();
                    img1->setUseTexture(false);
                    img1->setImageType(OF_IMAGE_COLOR);
                    img1->loadImage(dragList[imgCounter-1].path);
                    mw = (float) img1->width;
                    mh = (float) img1->height;
                    p1 = ofxMNOTools::scaleToFitKeepRatio(mw, mh, mfbo->getWidth(), mfbo->getHeight());
                    img1->resize(p1.width,p1.height);
                        
                    img2 = new ofImage();
                    img2->setUseTexture(false);
                    img2->setImageType(OF_IMAGE_COLOR);
                    img2->loadImage(dragList[imgCounter].path);
                    mw = (float) img2->width;
                    mh = (float) img2->height;
                    p2 = ofxMNOTools::scaleToFitKeepRatio(mw, mh, mfbo->getWidth(), mfbo->getHeight());
                    img2->resize(p2.width,p2.height);
                }
                alpha1 = 0;
                
                drawOnce = true;                
                loadImg = false;
            }
        }
    }   
    
    void _update(ofEventArgs &e)
    {
        if(!loadImg)
        {
            ofEnableAlphaBlending();
            
            if(drawOnce)
            {
                if(imgCounter == 1) 
                    drawImageOnceAlphaIn(img1, &p1);
                drawOnce = false;
                drawImageOnce(img1, &p1);
            }
            
            mfbo->begin();            
            ofClear(0);            
            
            //IMAGE 1
            ofSetColor(255, (255-alpha1));
            if(!img1->isUsingTexture())updateImg(img1);
            img1->draw(p1.x,p1.y);
            
            //IMAGE 2
            ofSetColor(255, alpha1);
            if(!img2->isUsingTexture())updateImg(img2);
            img2->draw(p2.x,p2.y);
            
            mfbo->end();
            
            mfbo->readToPixels(pix);
            mVidSaver->addFrame(pix.getPixels(), 0.05); //0.05*9=0.45
            
            alpha1 += FADE_TIME;
            
            if(alpha1 >= 255) 
            {
                imgCounter++;
                if(imgCounter > dragList.size()-1)
                {                    
                    drawImageOnce(img2, &p2);
                    drawImageOnceAlphaOut(img2, &p2);
                    mVidSaver->finishMovie();
                }
                else
                {
                    img1->clear();
                    img2->clear();
                    delete img1, img2;
                    img1 = NULL;
                    img2 = NULL;
                    loadImg = true;
                }                
            }
        }
    };
    
    void _draw(ofEventArgs &e) 
    {
        ofSetColor(255, 150);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        ofSetColor(0);
        string tempString = ofToString(imgCounter)+"/"+ofToString(dragList.size()-1);        
        ofRectangle rect = ttf.getStringBoundingBox(tempString, 0,0);
        ttf.drawString(tempString, ofGetWidth()/2-rect.width/2, ofGetHeight()/2-rect.height/2);
    };

    void updateImg(ofImage *img)
    {        
        const ofPixels& pix = img->getPixelsRef();
        img->getTextureReference().allocate(pix.getWidth(),pix.getHeight(),ofGetGlInternalFormat(pix));
        img->setUseTexture(true);
        img->update();
    };
    
    //image draw helper
    void drawImageOnce(ofImage *img, ofRectangle *p)
    {
        mfbo->begin();
        ofClear(0);
        
        ofSetColor(255);
        if(!img->isUsingTexture())updateImg(img);
        img->draw(p->x,p->y);
        
        mfbo->end();
        mfbo->readToPixels(pix);
        
        int timer = (dragList[imgCounter-1].isExtra) ? specialTime : normalTime;
        mVidSaver->addFrame(pix.getPixels(), timer);
    }
    
    void drawImageOnceAlphaIn(ofImage *img, ofRectangle *p)
    {
        int tempAlpha = 0;
        while(tempAlpha < 255)
        {
            mfbo->begin();
            ofClear(0);
            
            ofSetColor(255, tempAlpha);
            if(!img->isUsingTexture())updateImg(img);
            img->draw(p->x,p->y);
            
            mfbo->end();
            mfbo->readToPixels(pix);
            
            mVidSaver->addFrame(pix.getPixels(), 0.05);
            
            tempAlpha += FADE_TIME;
        }
    }
    
    void drawImageOnceAlphaOut(ofImage *img, ofRectangle *p)
    {
        int tempAlpha = 255;
        while(tempAlpha > 0)
        {
            mfbo->begin();
            ofClear(0);
            
            ofSetColor(255, tempAlpha);
            if(!img->isUsingTexture())updateImg(img);
            img->draw(p->x,p->y);
            
            mfbo->end();
            mfbo->readToPixels(pix);
            
            mVidSaver->addFrame(pix.getPixels(), 0.05);
            
            tempAlpha -= FADE_TIME;
        }
    }
};

#endif
