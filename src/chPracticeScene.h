//
//  chPracticeScene.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#ifndef __chordrina__chPracticeScene__
#define __chordrina__chPracticeScene__

#include <iostream>
#include <vector>
#include <string>
#include "chScene.h"
#include "chImage.h"
#include "chChord.h"

using namespace std;

class chProgressionChord {
public:
    chChord chord = chChord(NULL, 0);
    double x = 0.5, y = 0.5;
    double currentx = 0.5, currenty = 0.5;
    static ofxTrueTypeFontUC * font;
    
    chProgressionChord(const chChord & c) {
        chord = c;
    }
    
    void draw() {
        ofSetColor(255, 255, 255);
        string name = chord.getFirstName();
        double this_width = chProgressionChord::font->stringWidth(name);
        double this_height = chProgressionChord::font->stringHeight(name);
        std::cerr << currentx << "," << currenty << std::endl;
        chProgressionChord::font->drawString(chord.getFirstName(),
                                             currentx * ofGetWidth() - this_width/2.0,
                                             currenty * ofGetHeight() - this_height/2.0);
    }
    
    void move() {
        double distx = x - currentx;
        if (fabs(distx) > 1e-6) {
            double speed = distx / 60;
            currentx += speed;
        }
    }
};

class chProgression {
public:
    std::vector<chProgressionChord> chords;
    void addChord(const chChord & chord);
    int size() {
        return chords.size();
    }
};


class chPracticeScene : public chScene {
public:
    virtual void setup();
    virtual void update();
    virtual void draw();
    
protected:
    chImage bgImg = chImage("background", "Img/bg.jpg");
    
    chImage test = chImage("outer_circle", "Img/outer_circle.png");
    
    std::vector<chProgression> progression;
    size_t current_progression_indx = 0;
};

#endif /* defined(__chordrina__chPracticeScene__) */
