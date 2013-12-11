//
//  chPlayScene.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#ifndef __chordrina__chPlayScene__
#define __chordrina__chPlayScene__

#include <iostream>
#include "chScene.h"

class PianoChord {
public:
    double time;
    string name;
    bool is_correct = false;
    bool should_draw = false;
    PianoChord(double time, string name) : time(time), name(name) {};
};

class chPlayScene : public chScene {
public:
    virtual void setup();
    virtual void update();
    virtual void draw();
    
protected:
    ofSoundPlayer song;
    void loadChord();
    
    double start_time = 0;
    double current_time = 0;
    
    vector<PianoChord> chords;
    double end_time = 0;
    size_t current_chord = 0;
    
    chImage bgImg = chImage("stage_background", "Img/stage_bg.png");
    chImage spotLight = chImage("spotlight", "Img/spotlight.png");
    
    
};

#endif /* defined(__chordrina__chPlayScene__) */
