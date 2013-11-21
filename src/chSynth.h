//
//  chSynth.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
// A fluidsynth wrapper
// Mostly copied from Ge's y-synth.cpp

// Need to run
// install_name_tool -change /usr/local/lib/libfluidsynth.1.dylib @executable_path/libfluidsynth.1.dylib chordrinaDebug
// After building the project

#ifndef __chordrina__chSynth__
#define __chordrina__chSynth__

#include <iostream>
#include <string>
#include <fluidsynth.h>
#include <pthread.h>


class chSynth {
public:
    chSynth(int sampleRate, int polyphony);
    ~chSynth();
    
    void setup();
    void setSoundFont(const char* filename);
    
    void programChange( int channel, int program );
    void controlChange( int channel, int data2, int data3 );
    void noteOn( int channel, float pitch, int velocity );
    void pitchBend( int channel, float pitchDiff );
    void noteOff( int channel, int pitch );
    void allNotesOff( int channel );
    bool synthesize2( float* buffer, unsigned int numFrames );

protected:
    
    int sample_rate = 441000;
    int polyphony = 64;
    std::string font_path = "";
    
    fluid_settings_t * fl_settings = NULL;
    fluid_synth_t * fl_synth = NULL;
    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    void cleanup();
    
};

#endif /* defined(__chordrina__chSynth__) */
