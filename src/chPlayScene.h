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


enum ISCORRECT {
    NEW,
    CORRECT,
    WRONG
};

class PianoChord {
public:
    double time;
    string name;
    ISCORRECT is_correct = NEW;
    bool should_draw = false;
    PianoChord(double time, string name) : time(time), name(name) {};
};

class chPlayScene : public chScene {
public:
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void pause();
    
protected:
    ofSoundPlayer song;
    ofSoundPlayer applaud;
    void loadChord();
    
    double start_time = 0;
    double current_time = 0;
    
    vector<PianoChord> chords;
    double end_time = 0;
    size_t current_chord = 0;
    
    chImage bgImg = chImage("stage_background", "Img/stage_bg.png");
    chImage spotLight = chImage("spotlight", "Img/spotlight.png");
    
    vector<chImage> dots;
    chImage dot = chImage("bubble", "Img/bubble.png");
    
    chImage perfect = chImage("perfect", "Img/perfect.png");
    chImage goodjob = chImage("goodjob", "Img/goodjob.png");
    
    int current_streak = 0;
    int current_perfect_streak = 0;
    
    // drums
    vector<double> hihat;
    vector<double> kick;
    vector<double> snare;
    void loadDrumFile(string filename, vector<double>& dest);
    void loadDrums();
};

#endif /* defined(__chordrina__chPlayScene__) */
