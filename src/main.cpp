#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "Cocoa/Cocoa.h"

//========================================================================

int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 300, 500, OF_WINDOW);			// <-------- setup the GL context

    if (NSApp)
    {
    	id menubar = [[NSMenu new] autorelease];
        id appMenuItem = [[NSMenuItem new] autorelease];
        
        [menubar addItem:appMenuItem];
        [NSApp setMainMenu:menubar];
        
        id appMenu = [[NSMenu new] autorelease];
        
        id appName = [[NSProcessInfo processInfo] processName];
        
        id aboutTitle = [@"About " stringByAppendingString:appName];
        id aboutMenuItem = [[[NSMenuItem alloc] initWithTitle:aboutTitle 
                                                       action:@selector(orderFrontStandardAboutPanel:)
                                                keyEquivalent:@""] autorelease];
        [appMenu addItem:aboutMenuItem];
        
        id quitTitle = [@"Quit " stringByAppendingString:appName];
        id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle 
                                                      action:@selector(terminate:)
                                               keyEquivalent:@"q"] autorelease];
        [appMenu addItem:quitMenuItem];
        
        [appMenuItem setSubmenu:appMenu];
    }
    
    NSLog(@":: %@", [[NSApp mainWindow] contentView]);
    NSLog(@":: %@", [[NSApplication sharedApplication] mainWindow]);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
