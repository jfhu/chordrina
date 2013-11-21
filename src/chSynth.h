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

class chSynth {
public:
    chSynth(int sampleRate, int polyphony);
    ~chSynth();
    
    void setup();
    void setSoundFont(const char* filename);
    
protected:
    
    int sample_rate = 441000;
    int polyphony = 64;
    std::string font_path = "";
    
    fluid_settings_t * fl_settings = NULL;
    fluid_synth_t * fl_synth = NULL;
    
    void cleanup();
    
};

#endif /* defined(__chordrina__chSynth__) */
