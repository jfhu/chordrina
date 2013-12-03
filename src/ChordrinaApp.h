#pragma once

#include "ofMain.h"

#include "chMidiListener.h"
#include "chScene.h"
#include "chAppState.h"
#include "chSynth.h"

class ChordrinaApp : public ofBaseApp {

private:
    // scenes
    chMenuScene * menu_scene = new chMenuScene();
    chLearningScene * learning_scene = new chLearningScene();
    chSettingScene * setting_scene = new chSettingScene();
    chPracticeScene * practice_scene = new chPracticeScene();
    chPlayScene * play_scene = new chPlayScene();

    // global state
    chAppState * app_state = chAppState::instance();

    // audio
    int bufferSize = 512;
    int sampleRate = 44100;
    int polyphony = 64;
    float volume = 1.0f;
    ofSoundStream soundStream;
    chSynth * synth = new chSynth(sampleRate, polyphony);


public:
    void setup();
    void update();
    void draw();

    // Audio I/O
    void audioOut(float * buffer, int bufferSize, int nChannels);

    void keyPressed(int key);
    //		void keyReleased(int key);
    //		void mouseMoved(int x, int y );
    //		void mouseDragged(int x, int y, int button);
    //		void mousePressed(int x, int y, int button);
    //		void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    //		void dragEvent(ofDragInfo dragInfo);
    //		void gotMessage(ofMessage msg);
    
};
