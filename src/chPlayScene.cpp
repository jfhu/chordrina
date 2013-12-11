//
//  chPlayScene.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#include "chPlayScene.h"
#include <fstream>

using namespace std;

ofxTrueTypeFontUC * font = new ofxTrueTypeFontUC();

void chPlayScene::setup() {
    bgImg.tmp_a = 255;
    spotLight.tmp_a = 255;
    
    start_time = 0;
    current_time = 0;
    end_time = 0;
    current_chord = 0;
    chords.clear();
    
    loadChord();
    font->loadFont("Fonts/Cutie Patootie.ttf", 20);

    song.loadSound("Song/song_no_drums_no_piano.mp3");
    
    chords[3].is_correct = true;
}


void chPlayScene::update() {
    
    if (fabs(start_time) == 0) {
        if (ofGetElapsedTimef() > 3.0) {
            song.play();
            start_time = ofGetElapsedTimef();
        }
    }
    
    {
        current_time = ofGetElapsedTimef() - start_time;
        if (start_time == 0) current_time -= 3;
        
        for (size_t i = 0; i < chords.size(); i++) {
            double offset = chords[i].time - current_time;
            if (offset < 6.0 && offset > -1.0) {
                chords[i].should_draw = true;
            }
        }
    }
}


void chPlayScene::draw() {
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    double spot_x = 0.2*ofGetWidth() - 140;
    double spot_y = 0.5*ofGetHeight() - 340;
    spotLight.draw(spot_x, spot_y, 500, 500);
    
    for (size_t i = 0; i < chords.size(); i ++) {
        if (!chords[i].should_draw) {
            continue;
        }
        
        double offset = chords[i].time - current_time;
        double relx = (offset) / 5.0;
        
        double x = relx * ofGetWidth();
        double y = 0.5 * ofGetHeight();
        
        ofSetColor(0, 0, 0, 150);
        if (chords[i].is_correct) {
            ofSetColor(0, 10, 250, 150);
        }
        ofCircle(x, y, 50);
        
        ofSetColor(255, 255, 255, 255);
        double str_width = font->stringWidth(chords[i].name);
        double str_height= font->stringHeight(chords[i].name);
        font->drawString(chords[i].name, x - str_width/2.0, y + 10);
    }
    
    if (current_time > end_time) {
        ofSetColor(150, 0, 0);
        ofCircle(ofGetWidth()/2.0, ofGetHeight()/2.0, 100);
        ofSetColor(255, 255, 255);
        double width = font->stringWidth("Restart");
        font->drawString("Restart", (ofGetWidth()-width)/2.0, ofGetHeight()/2.0+10);
    }
}

void chPlayScene::loadChord() {
    const double OFFSET = 3.0;
    ifstream infile(ofToDataPath("Song/chord.txt").c_str());
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        double start, t;
        string name;
        ss >> start >> t;
        ss.ignore(1); // one space
        getline(ss, name);
        chords.push_back(PianoChord(start + OFFSET, name));
        end_time = t + OFFSET;
    }
}
