//
//  chLearningScene.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include <map>

#include "chLearningScene.h"
#include "chAppState.h"
#include "chChord.h"


void chLearningScene::setup() {
    
    // Set background alpha
    bgImg.tmp_a = 255;

    // Create background Dots
    for (size_t i = 0; i < 20; i ++) {
        bgDots.push_back(chImage("dot", "Img/dot.png"));
        bgDots[i].width = bgDots[i].height = 220 + ofRandom(0, 100);
        bgDots[i].dy = ofRandom(.4, .8);
        bgDots[i].relx = ofRandom(0, 1);
        bgDots[i].rely = ofRandom(0, 1);
        bgDots[i].tmp_a = 0; // starting alpha
        bgDots[i].a = 150; // max alpha
    }
    
}

void chLearningScene::update() {
    
    // Move Background Dots
    for (size_t i = 0; i < bgDots.size(); i ++) {
        bgDots[i].move();
        bgDots[i].dx += ofRandom(-.05, .05);
        bgDots[i].width = bgDots[i].height = bgDots[i].width + ofRandom(-.8, .8);
        // If out of screen, fade out
        if (bgDots[i].relx < 0 || bgDots[i].relx > 1 || bgDots[i].rely < 0 || bgDots[i].rely > 1) {
            bgDots[i].a = 0;
        }
        // If faded out, reposition
        if (bgDots[i].tmp_a <= 0) {
            bgDots[i].relx = ofRandom(0, 1);
            bgDots[i].rely = ofRandom(0, 1);
            bgDots[i].dy = ofRandom(.4, .8);
            bgDots[i].dx = 0;
            bgDots[i].tmp_a = 0;
            bgDots[i].a = 150;
        }
    }
}

std::map<int, ofxTrueTypeFontUC*> helveticas;
void draw_text(std::string text, double xoffset) {
    double x = ofGetWidth() / 2.0;
    double y = ofGetHeight() / 2.0;
    int size = (int)(min(x, y) * 0.1);
    
    if (helveticas.find(size) == helveticas.end()) {
        ofxTrueTypeFontUC * new_font = new ofxTrueTypeFontUC();
        new_font->loadFont("Fonts/Helvetica Neue.ttf", size);
        helveticas[size] = new_font;
    }
    
    ofxTrueTypeFontUC * font = helveticas[size];
    double text_width = font->stringWidth(text);
    font->drawString(text, x + xoffset - text_width / 2.0, y + size / 2.0);
}


void chLearningScene::draw() {
    // Draw background image
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    // Draw floating dots
    for (size_t i = 0; i < bgDots.size(); i++) {
        bgDots[i].drawCenter();
    }

    
    
    // Draw two circles
	double x = ofGetWidth() / 2.0;
	double y = ofGetHeight() / 2.0;
	double diameter = min(x, y) * 0.3;
    
    // Current Chord
    std::vector<int> keydown = chAppState::instance()->midi->getKeys();

    chChord chord(keydown);
    
    // TODO: chord.getNames() and see if expected_chord is in the array
    std::string current_chord = chord.getName();
    
    // Expected Chord
    std::string expected_chord = chAppState::instance()->current_chord;
    
    // Left Circle
    ofSetColor(57, 135, 238);
    ofCircle(x-diameter, y, diameter);
    
    // Right Circle
    ofSetColor(238, 57, 135);
    if (current_chord == expected_chord) {
        ofSetColor(135, 238, 57);
    }
	ofCircle(x+diameter, y, diameter);
    
    // font color
    ofSetColor(255, 255, 255);
    
    // draw target chord
    draw_text(expected_chord, -diameter);
    
    // draw current chord
    draw_text(current_chord, diameter);

}
