//
//  chAppState.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#ifndef __chordrina__chAppState__
#define __chordrina__chAppState__

#include <iostream>
#include <string>
#include "chMidiListener.h"
#include "chSynth.h"
#include "chScene.h"

class ChordrinaApp;

class chAppState {
public:
    static chAppState * instance();

    // some global stuff
    chMidiListener * midi = new chMidiListener();
    chSynth * synth = NULL;

    // state
    bool should_show_debug = true;
    bool should_show_setting = true;
    SCENE current_scene_type = SCENE_LEARN;
    chScene* current_scene = NULL;
    std::string current_chord = "A Maj";

private:
    chAppState() {
        midi->setup();
    };
    chAppState(chAppState const&) {};
    static chAppState * m_instance;

    // App state

};

#endif /* defined(__chordrina__chAppState__) */
