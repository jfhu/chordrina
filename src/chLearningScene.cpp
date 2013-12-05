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
#include <cmath>

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
            bgDots[i].b = 255 - ofRandom(0, 40);
            bgDots[i].g = 255 - ofRandom(0, 40);
        }
    }
}

std::map<int, ofxTrueTypeFontUC*> fonts;
void draw_text(std::string text, double xoffset, double y) {
    double x = ofGetWidth() / 2.0;
//    double y = ofGetHeight() / 2.0;
    int size = (int)(y * 0.15);

    if (fonts.find(size) == fonts.end()) {
        ofxTrueTypeFontUC * new_font = new ofxTrueTypeFontUC();
        new_font->loadFont("Fonts/Cutie Patootie.ttf", size);
        fonts[size] = new_font;
    }

    ofxTrueTypeFontUC * font = fonts[size];
    double text_width = font->stringWidth(text);
    font->drawString(text, x + xoffset - text_width / 2.0, y + size / 2.0);
}


extern std::string chordList[];
extern std::string qualityList[];
void chLearningScene::draw() {
    // Draw background image
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());

    // Draw floating dots
    for (size_t i = 0; i < bgDots.size(); i++) {
        bgDots[i].drawCenter();
    }

    static double left_rand = ofRandom(0, pi);
    static double right_rand = ofRandom(0, pi);

    // Draw two circles
	double x = ofGetWidth() / 2.0;
	double y = ofGetHeight() / 2.0;
	double diameter = min(x, y) * 0.3;
    double left_y = y + sin( (fmod((double)ofGetElapsedTimef(), 2*PI) + left_rand)*3 ) * 5;
    double right_y = y + sin((fmod((double)ofGetElapsedTimef(), 2*PI) + right_rand)*3) * 5;

    // Current Chord
    std::vector<int> keydown = chAppState::instance()->midi->getKeys();
    static std::vector<int> prevKeyDown = keydown;
    static double lastTime_diff = 0;

    cout << "time: " << ofGetElapsedTimef() << " " << lastTime_diff << endl;
    bool same = true;
    if (keydown.size() == prevKeyDown.size()) {
        for (size_t i = 0; i < keydown.size(); i++) {
            cout << keydown[i] << " " << prevKeyDown[i] << endl;
            if (keydown[i] != prevKeyDown[i]) {
                same = false;
                break;
            }
        }
    } else {
        same = false;
    }

    if (same){
        cout << "same" << endl;
    }
    else {
        lastTime_diff = ofGetElapsedTimef();
        cout << "diff" << endl;
        prevKeyDown = keydown;

    }

        chChord chord(keydown);

        // Modified: chord.getNames() and see if expected_chord is in the array
        string current_chord;
        vector<string> current_chords = chord.getNames();

    // // Left Circle
    // ofSetColor(57, 135, 238);
    // ofCircle(x-diameter, left_y, diameter);

    // // Right Circle


        chord.printName();
        cout << current_score << " " << best_score << endl;
        ofDrawBitmapString("Current Score " + ofToString(current_score), ofGetWidth() - 130, 30);
        ofDrawBitmapString("Best Score " + ofToString(best_score), ofGetWidth() - 130, 45);

        // Expected Chord
        std::string expected_chord = chAppState::instance()->current_chord;

        // Left Circle
        ofSetColor(57, 135, 238);
        ofCircle(x-diameter, left_y, diameter);

    
    if (should_draw_green_ball) {
            // draw green ball
        ofSetColor(135, 238, 57);
        ofCircle(x+diameter, right_y, diameter);

        // draw target chord
        ofSetColor(255, 255, 255);
        draw_text(expected_chord, -diameter, left_y);
        
        // draw current chord
        ofSetColor(255, 255, 255);
        std::cerr << should_draw_text << std::endl;
        draw_text(should_draw_text, diameter, right_y);

        
        if (ofGetElapsedTimef() - last_correct_time > 1.5) {
            should_draw_green_ball = false;
            
            
            std::string rand_chord = chordList[rand() % 12];
            std::string rand_quality = qualityList[rand() % 5];
            chAppState::instance()->current_chord = rand_chord + " " + rand_quality;
            current_chord_correct = false;
            lastTime_diff = ofGetElapsedTimef() + 1;
        }
        return;
    }
    
    // Right Circle
    ofSetColor(238, 57, 135);
    ofCircle(x+diameter, right_y, diameter);

        if ((ofGetElapsedTimef() - lastTime_diff) > 0.5){
            // Check if the user is playing the right chord
            for (int i = 0; i < current_chords.size(); i++){
                if (current_chords[i] == expected_chord) {

                    // User played correct chord

                    if (!current_chord_correct) {
                        current_score ++;
                        if (current_score > best_score) {
                            best_score = current_score;
                        }
                        
                        should_draw_green_ball = true;
                        should_draw_text = current_chord;
                        last_correct_time = ofGetElapsedTimef();

                    }

//                    current_chord_correct = true;

                    current_chord = current_chords[i];
                    
                    ofSetColor(135, 238, 57);
                    ofCircle(x+diameter, right_y, diameter);

                    // font color
                    ofSetColor(255, 255, 255);

                    // draw target chord
                    draw_text(expected_chord, -diameter, left_y);

                    // draw current chord
                    draw_text(current_chord, diameter, right_y);

                    return;
                }
            }

            // User played wrong chord
            if (keydown.size() > 0)
                current_score = 0;
            current_chord = current_chords[0];

            // ofCircle(x+diameter, right_y, diameter);

            ofSetColor(255, 255, 255);

            // draw target chord
            draw_text(expected_chord, -diameter, left_y);

            // draw current chord
            draw_text(current_chord, diameter, right_y);

            return;
        }

        // Didn't  play chord
        current_chord = "?";
        // font color
        ofSetColor(255, 255, 255);

        // draw target chord
        draw_text(expected_chord, -diameter, left_y);

        // draw current chord
        draw_text(current_chord, diameter, right_y);
// =======
//             draw_text(current_chord, diameter, right_y);

//             return;
//         }
//     }

//     // Didn't  play the correct chord
//     ofSetColor(238, 57, 135);
//     current_chord = current_chords[0];
// 	ofCircle(x+diameter, right_y, diameter);

//     // font color
//     ofSetColor(255, 255, 255);

//     // draw target chord
//     draw_text(expected_chord, -diameter, left_y);

//     // draw current chord
//     draw_text(current_chord, diameter, right_y);
// >>>>>>> parent of fa09845... Revert "practise scene"

}
