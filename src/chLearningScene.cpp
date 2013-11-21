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

std::map<int, ofxTrueTypeFontUC*> helveticas;

void draw_text(std::string text, double xoffset) {
    double x = ofGetWidth() / 2.0;
    double y = ofGetHeight() / 2.0;
    int size = (int)(min(x, y) * 0.15);
    
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
    
    // draw background circle
    // TODO: animated position
	double x = ofGetWidth() / 2.0;
	double y = ofGetHeight() / 2.0;
	double diameter = min(x, y) * 0.6;
    
    // Current Chord
    std::vector<int> keydown = chAppState::instance()->midi->getKeys();
    //    for (int i = 0; i < keydown.size(); i++) {
    //        std::cerr << keydown[i] << " ";
    //    }
    //    std::cerr << std::endl;
    chChord chord(keydown);
    std::string current_chord = chord.getName();
    
    // Expected Chord
    std::string expected_chord = chAppState::instance()->current_chord;
    
    // Left Circle
    ofSetColor(57, 135, 238, 150);
    ofCircle(x-diameter/1.3, y, diameter);
    
    // Right Circle
    ofSetColor(238, 57, 135, 150);
    if (current_chord == expected_chord) {
        ofSetColor(135, 238, 57, 150);
    }
	ofCircle(x+diameter/1.3, y, diameter);
    
    // font color
    ofSetColor(255, 255, 255);
    
    // draw target chord
    draw_text(expected_chord, -diameter/1.3);
    
    // draw current chord
    draw_text(current_chord, diameter/1.3);
}