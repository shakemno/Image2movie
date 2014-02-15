#include "testApp.h"
#include "SettingsSingleton.h"

//--------------------------------------------------------------
void testApp::exit()
{     
    if(exporter != NULL)
    {
        exporter->stop();
        delete exporter;
        exporter = NULL;
    }
    delete gui; 
}
//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    ofSetDataPathRoot("../Resources/data/");
    
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.allowExt("jpeg");
    dir.allowExt("gif");
    
    container.setSize(ofGetWidth(), ofGetHeight());
    container.y = 5;
	container.setPos(5, 5, 0);
    container.disableAllEvents();
    
    SettingsSingleton *s = SettingsSingleton::getInstance();
    s->setWidth(1024);
    s->setHeight(768);
    s->setNormalTime(1);
    s->setSpecialTime(3);
    
    float canvasWidth = ofGetWidth()-20;
    float fullWidth = canvasWidth-15;
    float halfWidth = (fullWidth/2)-6;
    
    gui = new ofxUICanvas(10,ofGetHeight()-200, canvasWidth, 190);
    gui->setColorBack(ofColor(80, 230)); 
//    gui->setFont("NewMedia Fett.ttf");  
    
    //size input
    gui->addWidgetDown(new ofxUILabel("OUPUT SIZE WIDTH / HEIGHT", OFX_UI_FONT_SMALL)); 
    
    gui->addWidgetDown(new ofxUITextInput(halfWidth, "W", ofToString(s->getWidth()), OFX_UI_FONT_MEDIUM)); 
    ofxUITextInput* inputW = (ofxUITextInput *) gui->getWidget("W"); 
    inputW->setAutoClear(false);

    gui->addWidgetRight(new ofxUITextInput(halfWidth, "H", ofToString(s->getHeight()), OFX_UI_FONT_MEDIUM)); 
    ofxUITextInput* inputH = (ofxUITextInput *) gui->getWidget("H"); 
    inputH->setAutoClear(false); 
    
    //time input
    gui->addWidgetDown(new ofxUILabel("STANDARD TIME / SPECIAL TIME", OFX_UI_FONT_SMALL)); 
    
    gui->addWidgetDown(new ofxUITextInput(halfWidth, "T", ofToString(s->getNormalTime()), OFX_UI_FONT_MEDIUM)); 
    ofxUITextInput* inputT = (ofxUITextInput *) gui->getWidget("T"); 
    inputT->setAutoClear(false);
    
    gui->addWidgetRight(new ofxUITextInput(halfWidth, "TS", ofToString(s->getSpecialTime()), OFX_UI_FONT_MEDIUM)); 
    ofxUITextInput* inputTS = (ofxUITextInput *) gui->getWidget("TS"); 
    inputTS->setAutoClear(false); 
    
    //export
    gui->addWidgetDown(new ofxUILabelButton(fullWidth, false, "EXPORT", OFX_UI_FONT_MEDIUM));
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->setVisible(false);
    
    mTimestamp = ofGetElapsedTimef();
    
    isRecording = 0;
    
    ofFbo::Settings setFbo;
    setFbo.width             = s->getWidth();
    setFbo.height            = s->getHeight();
    setFbo.internalformat    = GL_RGB;
    setFbo.useDepth			= false;
    
    mfbo = new ofFbo();
    mfbo->allocate(setFbo);
    
    mfbo->begin();
    ofClear(255,255,255, 0);
    mfbo->end();
    
    ttf.loadFont("GUI/NewMedia Fett.ttf", 12);
    
    needsToBeDropped = true;
    isGuiVisible = false;
}

//--------------------------------------------------------------
void testApp::update()
{
    bool oldNeedsToBeDropped = needsToBeDropped;
    needsToBeDropped = (container.children.size() == 0) ? true : false;
    
    //toggle gui here
    if(oldNeedsToBeDropped != needsToBeDropped)
    {
        toggleGui();
    }
}

//--------------------------------------------------------------
void testApp::draw()
{    
    ofBackgroundGradient(ofColor(80,80,80), ofColor(10,10,10));
    
	ofSetColor(255);
    
    if(needsToBeDropped)
    {
        //ofDrawBitmapString("Drop me a folder", 85, 200);
        
        string tempString = "DROP ME A FOLDER...\n\nPress 'h' to hide settings\npanel and highlight the\nimages with special time.\nUp and down arrows are\nfor scrolling.\n\nWe still got a bug with\nresizing to a smaller\nsize and going back larger,\njust restart for now.";        
        ofRectangle rect = ttf.getStringBoundingBox(tempString, 0,0);
        ttf.drawString(tempString, ofGetWidth()/2-rect.width/2, ofGetHeight()/2-rect.height/2);
    }
    else container.draw();
    
    if(isRecording <= 2)
    {        
//        ofSetColor(255, 150);
//        ofRect(0, 0, ofGetWidth(), ofGetHeight());
//        ofPushMatrix();
//            ofSetColor(0);
//            ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 10);
//            ofRotate( ofGetFrameNum()*10 );
//            ofLine(-10, 0, 10, 0);
//            ofLine(0, -10, 0, -10);
//        ofPopMatrix();
//        
//        ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15); 
    }
}


//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    
    cout << "--> guiEvent - name: " << name << " - " << isRecording << endl;
    
    SettingsSingleton *s = SettingsSingleton::getInstance();
    
    if(name == "EXPORT")
    {
        //hack, callback fires twice
        isRecording++;
        if(isRecording >= 2)
        {            
            gui->disableMouseEventCallbacks();
            exportMovie();
        }
    }
    else if(name == "W")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget; 
        s->setWidth(ofToInt(textinput->getTextString()));
        
        /*
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: "; 
            //            ofUnregisterKeyEvents((testApp*)this); 
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: "; 
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: "; 
            //            ofRegisterKeyEvents(this);             
        }        
        */
    
    }
    else if(name == "H")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget; 
        s->setHeight(ofToInt(textinput->getTextString()));        
    }
    else if(name == "T")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget; 
        s->setNormalTime(ofToInt(textinput->getTextString()));        
    }
    else if(name == "TS")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget; 
        s->setSpecialTime(ofToInt(textinput->getTextString()));        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch(key)
    {
        case OF_KEY_DOWN:
            if (container.height < ofGetHeight()) break;
            container.y -= 5;
            if(container.y < -(container.height-ofGetHeight()))
            {
                container.y = -(container.height-ofGetHeight());
                break;
            }  
            for(int i = 0; i < container.children.size(); i++)
            {
                ofxObject *temp = container.children[i];
                temp->y -= 5;
                temp->setPos(0,temp->y,0);
            }       
            break;
        case OF_KEY_UP:            
            if (container.height < ofGetHeight()) break;
            container.y += 5;
            if(container.y > 5) 
            {
                container.y = 5;
                break;
            }
            for(int i = 0; i < container.children.size(); i++)
            {
                ofxObject *temp = container.children[i];
                temp->y += 5;
                temp->setPos(0,temp->y,0);
            }
            break;
        case 'r':
            container.y = 5;
            for(int i = 0; i < container.children.size(); i++)
            {
                //super hacky
                DragListObject *tempy = dragList[i];
                ofxObject *temp = container.children[i];
                temp->y = tempy->orgY;
                temp->setPos(0,temp->y,0);
            }
            break;
        case 'h':
            if(!needsToBeDropped) 
            {
                toggleGui();
            }; 
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    cout << "msg --->" << msg.message << endl;
    if(msg.message == "done_with_export")
    {   
        gui->enableMouseEventCallbacks();
        isRecording = 0;
        
        if(exporter != NULL)
        {
            exporter->stop();
            delete exporter;
            exporter = NULL;
        }
    }
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo info){
	
	if( info.files.size() > 0 )
    {
        dir.open(info.files[0]);
        if(dir.isDirectory()) 
        {
            saveDataPath = info.files[0];
            
            dir.listDir(info.files[0]);
            
            dragList.clear();
            
            float tempHeight = 0;
            
            for(int i = 0; i < dir.numFiles(); i++)
            {
                DragListObject *temp = new DragListObject( dir.getName(i), dir.getPath(i), (32*i), ofGetWidth()-10 );
                temp->setSize(ofGetWidth()-10, 32);
                temp->setPos(0, temp->y, 0);
                temp->disableMouseEvents();
                temp->disableAppEvents();
                
                container.addChild(temp);
        
                dragList.push_back( temp );
                
                tempHeight += 32;
            }
            
            container.setSize(ofGetWidth(), tempHeight);
            container.height = tempHeight;
        }
        else 
        {
            ofSystemAlertDialog("Not a directoy...!");
        }
    }
}

//--------------------------------------------------------------

void testApp::exportMovie()
{    
    
    SettingsSingleton *s = SettingsSingleton::getInstance();
    
    delete mfbo;
    
    //is it breaking here? something related to reallocating fbo
    
    ofFbo::Settings setFbo;
    setFbo.width             = s->getWidth();
    setFbo.height            = s->getHeight();
    setFbo.internalformat    = GL_RGB;
    setFbo.useDepth			= false;
    
    mfbo = new ofFbo();
    mfbo->allocate(setFbo);
    
    mfbo->begin();
    ofClear(255,255,255, 0);
    mfbo->end();
    
    if(exporter == NULL)
    {
        vector<dragObj> temp;
        
        for (int i = 0; i < dragList.size(); i++) 
        {
            dragObj tempObj;
            tempObj.path = dragList[i]->path;
            tempObj.isExtra = dragList[i]->isExtra;
            temp.push_back(tempObj);
        }
        
        exporter = new ExportMovieThread(mfbo, createFileName(), temp);
        exporter->start();
    }
    
    /*
    // init the movie saver
    mVidSaver.setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_HIGH);
    mVidSaver.setup(w, h, createFileName());
    
    ofImage *pixImg;
    ofFbo *fbo = new ofFbo();
    ofPixels *pix = new ofPixels(); 
    
    ofFbo::Settings s;
    s.width             = w;
    s.height            = h;
    s.internalformat    = GL_RGB;
    s.useDepth			= false;
    
    fbo->allocate(s);
    
    //sanity check if is recording
    for (int i = 0; i < dragList.size(); i++) 
    {
        pixImg = new ofImage();
        pixImg->loadImage(dragList[i]->path);
        
        fbo->begin();
        ofClear(255,255,255, 0);
        pixImg->draw(0,0, fbo->getWidth(), fbo->getHeight());
        fbo->end();
        
        fbo->readToPixels(*pix);
        
        mVidSaver.addFrame(pix->getPixels(), 0.5);
        
        delete pixImg;
    }
    delete fbo;
    delete pix;
    
    mVidSaver.finishMovie(); 
    */
}

//--------------------------------------------------------------

void testApp::toggleGui()
{
    isGuiVisible = !isGuiVisible; 
    gui->setVisible(isGuiVisible);
    setChildVisible(!isGuiVisible);
}

void testApp::setChildVisible(bool visi)
{
    for(int i = 0; i < container.children.size(); i++)
    {
        DragListObject *temp = static_cast<DragListObject *>(container.children[i]);
        if(visi) temp->enableMouseEvents();
        else temp->disableMouseEvents();
    }   
}

string testApp::createFileName()
{
    // create a uniqe file name
	ostringstream oss;
	oss << ofGetYear() << "-";
	oss << setw(2) << setfill('0') << ofGetMonth() << "-";
	oss << setw(2) << setfill('0') << ofGetDay() << "-";
	oss << setw(2) << setfill('0') << ofGetHours() << "-";
	oss << setw(2) << setfill('0') << ofGetMinutes() << "-";
	oss << setw(2) << setfill('0') << ofGetSeconds() << ".mov";
	return saveDataPath+"_"+oss.str();	
}
