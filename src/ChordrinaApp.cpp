#include "ChordrinaApp.h"
#include <iostream>
#include "chChord.h"

void ChordrinaApp::setup(){
    ofSetFrameRate(60);
    ofSetCircleResolution(96);
    // ofSetFullscreen(true);
	// ofEnableAlphaBlending();
    
    synth->setup();
    
    // soundStream.listDevices();
    // soundStream.setDeviceID(1);
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
}

void ChordrinaApp::update() {

}

void ChordrinaApp::draw(){
    
    switch (app_state->current_scene) {
        case SCENE_LEARN:
            learning_scene->draw();
            break;
        case SCENE_PRACTICE:
            practice_scene->draw();
            break;
        case SCENE_PLAY:
            play_scene->draw();
            break;
        default:
            std::cerr << "Unrecognized Scene: " << app_state->current_scene << std::endl;
            break;
    }

	if (app_state->should_show_setting) {
		setting_scene->draw();
	}

	if (app_state->should_show_debug) {
//		ofDrawBitmapString(ofToString(ofGetFrameRate(), 2)+"fps", 10, 15);
	}
}

void ChordrinaApp::audioOut(float * buffer, int bufferSize, int nChannels) {
//    std::cerr << ".";
    for (size_t i = 0; i < bufferSize; i ++) {
        buffer[i] = ofRandom(0, 1) * 0.1;
    }
}

void ChordrinaApp::windowResized(int w, int h) {
}


void ChordrinaApp::keyPressed(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
}
