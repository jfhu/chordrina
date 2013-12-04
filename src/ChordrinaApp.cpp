#include "ChordrinaApp.h"
#include <iostream>
#include "chChord.h"

void ChordrinaApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    // ofSetFullscreen(true);
	// ofEnableAlphaBlending();
    
    // Setup fluidsynth
    synth->setup();
    
    // Setup output sound
    // soundStream.listDevices();
    // soundStream.setDeviceID(1);
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    // Setup Scenes
    menu_scene->setup();
    learning_scene->setup();
    setting_scene->setup();
    practice_scene->setup();
    play_scene->setup();
    
    windowResized(ofGetWidth(), ofGetHeight());
}

void ChordrinaApp::update() {
    switch (app_state->current_scene_type) {
        case SCENE_LEARN:
            app_state->current_scene = learning_scene;
            break;
            
        case SCENE_PLAY:
            app_state->current_scene = play_scene;
            break;
            
        case SCENE_MENU:
            app_state->current_scene = menu_scene;
            break;
            
        case SCENE_PRACTICE:
            app_state->current_scene = practice_scene;
            break;
            
        default:
            break;
    }
    app_state->current_scene->update();
}

void ChordrinaApp::draw(){
    
    app_state->current_scene->draw();

	if (app_state->should_show_setting) {
		setting_scene->draw();
	}

	if (app_state->should_show_debug) {
        ofSetColor(255, 255, 255);
		ofDrawBitmapString(ofToString(ofGetFrameRate(), 1)+"fps", ofGetWidth() - 60, 15);
	}
    
}

void ChordrinaApp::audioOut(float * buffer, int bufferSize, int nChannels) {
    // I thought 'bufferSize' here should be 'numFrames'???
    synth->synthesize2(buffer, bufferSize);
}

void ChordrinaApp::windowResized(int w, int h) {

}


void ChordrinaApp::keyPressed(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
}
