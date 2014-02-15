#pragma once

#include "ofMain.h"
#include "DragListObject.h"
#include "ofxUI.h"
#include "ofxQTVideoSaver.h"
#include "ExportMovieThread.h"
#include "DragListContainer.h"

class testApp : public ofBaseApp
{
    private:    
        ofDirectory dir;
        string saveDataPath;
        vector <DragListObject *> dragList;
        
        ofxUICanvas *gui;   	
        void guiEvent(ofxUIEventArgs &e);
        
        int isRecording;
        ofxQtVideoSaver mVidSaver;
        float mTimestamp;
        
        ofFbo *mfbo;
        
        ExportMovieThread *exporter;
        
        DragListContainer container;
    
        bool needsToBeDropped, isGuiVisible;
    
        void setChildVisible(bool visi = true);
        void toggleGui();
        string createFileName();
        void exportMovie();
    
        ofTrueTypeFont ttf;
    
	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void gotMessage(ofMessage msg);
		void dragEvent(ofDragInfo dragInfo);
};
