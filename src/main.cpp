#include "ofMain.h"
#include "ChordrinaApp.h"

#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double alpha samples>=8 depth");
    ofSetupOpenGL(&window, 1024,768,OF_WINDOW);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ChordrinaApp());

}
