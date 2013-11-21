//
//  chSynth.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//
// Mostly copied from Ge's y-synth.cpp

#include "chSynth.h"
#include "ofMain.h"

chSynth::chSynth(int sample_rate, int polyphony) : sample_rate(sample_rate), polyphony(polyphony) {
    
    polyphony = min(max(polyphony, 0), 256);
    
}

chSynth::~chSynth() {
    cleanup();
}

void chSynth::setup() {
    // initialization
    ofLogNotice() << "chSynth: " << "initializing...";

    cleanup();
    
    fl_settings = new_fluid_settings();
    fluid_settings_setnum(fl_settings, "synth.sample-rate", (double)sample_rate);
    fluid_settings_setint(fl_settings, "synth.polyphony", polyphony);
    fl_synth = new_fluid_synth(fl_settings);
    setSoundFont("data/SoundFonts/rocking8m11e.sf2");
    
}

void chSynth::setSoundFont(const char* filename) {
    font_path = filename;    
    if (fluid_synth_sfload(fl_synth, font_path.c_str(), true) == -1) {
        std::cerr << "Cannot load font file: " << font_path << std::endl;
        exit(1);
    }
}

void chSynth::cleanup() {
    if (fl_settings) {
        delete_fluid_settings(fl_settings);
        fl_settings = NULL;
    }
    
    if (fl_synth) {
        delete_fluid_synth(fl_synth);
        fl_synth = NULL;
    }
}
