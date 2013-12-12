//
//  chPlayScene.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#include "chPlayScene.h" 
#include "chAppState.h"
#include <fstream>
#include <vector>


using namespace std;

ofxTrueTypeFontUC * font = new ofxTrueTypeFontUC();

#define NUM_DOT 500
#define NUM_DOT_EACH 100

void chPlayScene::setup() {
    bgImg.tmp_a = 255;
    spotLight.tmp_a = 255;
    
    dots.clear();
    for (size_t i = 0; i < NUM_DOT; i ++) {
        dot.relx = 0.5;
        dot.rely = 0.5;
        double direction = ofRandom(0, 2*pi);
        double velocity = ofRandom(0.0, 2);
        dot.dx = sin(direction)*velocity;
        dot.dy = cos(direction)*velocity;
        dot.r = ofRandom(128, 255);
        dot.g = ofRandom(128, 255);
        dot.b = ofRandom(128, 255);
        dot.a = 0;
        dot.tmp_a = 0;
        dot.width = dot.height = 10;
        dots.push_back(dot);
    }
    

    
    
    start_time = 0;
    current_time = 0;
    end_time = 0;
    current_chord = 0;
    chords.clear();
    
    loadChord();
    font->loadFont("Fonts/Cutie Patootie.ttf", 24);

    song.loadSound("Song/song_no_drums_no_piano.mp3");
}


void chPlayScene::update() {
    
    // Wait 3 seconds before the song plays
    if (fabs(start_time) == 0) {
        if (ofGetElapsedTimef() > 3.0) {
            song.play();
            start_time = ofGetElapsedTimef();
        }
    }
    
    // If chord is visible, mark it
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
    
    // See if it's correct
    vector<int> keydown = chAppState::instance()->midi->getKeys();
    chChord chord(keydown);
    PianoChord& cur_chord = chords[current_chord];
    

    
    // If we are close to this chord
    if (current_time - cur_chord.time < 0.2 && current_time - cur_chord.time > -1) {
        // and play it right
        if (chord.matchName(chords[current_chord].name)) {
            chords[current_chord].is_correct = CORRECT;
            
            if (current_chord < chords.size() - 1) {
                current_chord += 1;
            }
            
            
            // If close: show PERFECT
            cerr << current_time - cur_chord.time << endl;
            if (current_time - cur_chord.time > -0.7
                && current_time - cur_chord.time < -0.3) {
                cerr << "PERFECT" << endl;
                
                int counter = NUM_DOT_EACH;
                for (size_t i = 0; i < dots.size(); i ++) {
                    if (dots[i].tmp_a == 0) {
                        counter --;
                        dots[i].tmp_a = 250;
                        dots[i].a = 0;
                        dots[i].relx = 0.3 + ofRandom(-0.05, 0.05);
                        dots[i].rely = 0.5 + ofRandom(-0.05, 0.05);
                        double direction = ofRandom(0.2*pi, 1.8*pi);
                        double velocity = ofRandom(0.5, 5.5);
                        dots[i].dx = sin(direction)*velocity;
                        dots[i].dy = cos(direction)*velocity;
                    }
                    if (!counter) {
                        break;
                    }
                }
            }
            
        }
    }
    
    
    // If this chord passed
    if (current_time - cur_chord.time > 0.2) {
        // and we didn't play it right
        if (cur_chord.is_correct == NEW) {
            cur_chord.is_correct = WRONG;
            
            if (current_chord < chords.size() - 1) {
                current_chord += 1;
            }
            
            
            // show MISS
            cerr << "MISS" << endl;
        }
    }
    
    
    // update dots
    for (size_t i = 0; i < dots.size(); i ++) {
        dots[i].move();
        dots[i].dy += 0.2;
//        dots[i].tmp_a --;
    }
}


void chPlayScene::draw() {
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    double spot_x = 0.2*ofGetWidth() - 140;
    double spot_y = 0.5*ofGetHeight() - 340;
    spotLight.draw(spot_x, spot_y, 500, 500);
    
    // Draw dots
    for (size_t i = 0; i < dots.size(); i ++) {
        dots[i].drawCenter();
    }
    
    // Draw circles
    for (size_t i = 0; i < chords.size(); i ++) {
        if (!chords[i].should_draw) {
            continue;
        }
        
        double offset = chords[i].time - current_time;
        double relx = (offset) / 5.0;
        
        double x = (relx+0.2) * ofGetWidth();
        double y = 0.5 * ofGetHeight();
        
        switch (chords[i].is_correct) {
            case NEW:
                ofSetColor(0, 0, 0, 200);
                break;
            case CORRECT:
                ofSetColor(0, 255, 0, 200);
                break;
            case WRONG:
                ofSetColor(255, 0, 0, 200);
                break;
        }
        ofCircle(x, y, 60);
        
        ofSetColor(255, 255, 255, 255);
        double str_width = font->stringWidth(chords[i].name);
        double str_height= font->stringHeight(chords[i].name);
        font->drawString(chords[i].name, x - str_width/2.0, y + 10);
    }
    
    // If Ended, draw restart
    if (current_time > end_time) {
        ofSetColor(150, 0, 0);
        ofCircle(ofGetWidth()/2.0, ofGetHeight()/2.0, 100);
        ofSetColor(255, 255, 255);
        double width = font->stringWidth("Restart");
        font->drawString("Restart", (ofGetWidth()-width)/2.0, ofGetHeight()/2.0+10);
    }
    
    
    

}


void chPlayScene::loadChord() {
    const double OFFSET = 2;
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
