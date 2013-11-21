//
//  chSynth.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//
// Mostly copied from Ge's y-synth.cpp

#include "chSynth.h"
#include "chAppState.h"
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

    pthread_mutex_lock(&mutex);
    fl_settings = new_fluid_settings();
    fluid_settings_setnum(fl_settings, "synth.sample-rate", (double)sample_rate);
    fluid_settings_setint(fl_settings, "synth.polyphony", polyphony);
    fl_synth = new_fluid_synth(fl_settings);
    pthread_mutex_unlock(&mutex);

    setSoundFont("data/SoundFonts/rocking8m11e.sf2");

    // map program changes ---> what for?
    programChange( 0, 0 );
    programChange( 1, 79 );
    programChange( 2, 4 );
    programChange( 3, 10 );
    programChange( 4, 13 );

    chAppState::instance()->synth = this;
}

void chSynth::setSoundFont(const char* filename) {
    font_path = filename;
    pthread_mutex_lock(&mutex);
    if (fluid_synth_sfload(fl_synth, font_path.c_str(), true) == -1) {
        std::cerr << "Cannot load font file: " << font_path << std::endl;
        exit(1);
    }
    pthread_mutex_unlock(&mutex);
}

void chSynth::cleanup() {
    pthread_mutex_lock(&mutex);

    if (fl_settings) {
        delete_fluid_settings(fl_settings);
        fl_settings = NULL;
    }
    
    if (fl_synth) {
        delete_fluid_synth(fl_synth);
        fl_synth = NULL;
    }

    pthread_mutex_unlock(&mutex);
}



// Following copied from Ge's y-api

void chSynth::programChange( int channel, int program ) {
    if (fl_synth == NULL) return;
    if (program < 0 || program > 127) return;
    pthread_mutex_lock(&mutex);
    fluid_synth_program_change(fl_synth, channel, program);
    pthread_mutex_unlock(&mutex);
}

void chSynth::controlChange( int channel, int data2, int data3 ) {
    if (fl_synth == NULL) return;
    if (data2 < 0 || data2 > 127) return;
    pthread_mutex_lock(&mutex);
    fluid_synth_cc(fl_synth, channel, data2, data3);
    pthread_mutex_unlock(&mutex);
}

void chSynth::noteOn( int channel, float pitch, int velocity ) {
    if (fl_synth == NULL) return ;
    int pitch_i = (int)(pitch + .5f);
    float diff = pitch - pitch_i;
    pthread_mutex_lock(&mutex);
    if (diff != 0) {
        fluid_synth_pitch_bend(fl_synth, channel, (int)(8192+diff*8191) );
    }
    fluid_synth_noteon(fl_synth, channel, pitch, velocity);
    pthread_mutex_unlock(&mutex);
}

void chSynth::pitchBend( int channel, float pitchDiff ) {
    if (fl_synth == NULL) return;
    pthread_mutex_lock(&mutex);
    fluid_synth_pitch_bend(fl_synth, channel, (int)(8192+pitchDiff*8191));
    pthread_mutex_unlock(&mutex);
}

void chSynth::noteOff( int channel, int pitch ) {
    if (fl_synth == NULL) return;
    pthread_mutex_lock(&mutex);
    fluid_synth_noteoff(fl_synth, channel, pitch);
    pthread_mutex_unlock(&mutex);
}

void chSynth::allNotesOff( int channel ) {
    controlChange(channel, 120, 0x7B);
}

bool chSynth::synthesize2( float* buffer, unsigned int numFrames ) {
    if (fl_synth == NULL) return false;
    pthread_mutex_lock(&mutex);
    int retval = fluid_synth_write_float(fl_synth, numFrames, buffer, 0, 2, buffer, 1, 2);
    pthread_mutex_unlock(&mutex);
    return retval == 0;
}
