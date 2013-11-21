//
//  chSettingsUI.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#ifndef __chordrina__chSettingsUI__
#define __chordrina__chSettingsUI__

#define OFX_UI_NO_XML
#include "ofxUI.h"
#include "ofxTrueTypeFontUC.h"
#include "chScene.h"
#include <iostream>

class chSettingScene : public chScene {
public:
    virtual void setup();
    virtual void draw();
    
	ofxUICanvas * gui = new ofxUICanvas();
    std::vector<std::string> midi_choices;
    
	chSettingScene();
	void guiEvent(ofxUIEventArgs &e);
    
};


#endif /* defined(__chordrina__chSettingsUI__) */
