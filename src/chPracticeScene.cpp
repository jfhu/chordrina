//
//  chPracticeScene.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#include <algorithm>
#include "chAppState.h"
#include "chPracticeScene.h"

using namespace std;

ofxTrueTypeFontUC * chProgressionChord::font = new ofxTrueTypeFontUC();


void chProgression::addChord(const chChord & chord) {
    chProgressionChord c(chord);
    chords.push_back(c);
}

void chPracticeScene::setup() {
    chProgressionChord::font->loadFont("Fonts/Cutie Patootie.ttf", 35);
    
    bgImg.tmp_a = 255;
    
    arrow.relx = 0.3;
    arrow.rely = 0.65;
    arrow.tmp_a = 0;
    arrow.a = 255;
    
    // Progressions TODO: read them from midi file
    int arr[5] = {0};
    chProgression prog1;
    
    // F
    arr[0] = 65;
    arr[1] = 69;
    arr[2] = 72;
    prog1.addChord(chChord(arr, 3));
    
    // G
    arr[0] = 67;
    arr[1] = 71;
    arr[2] = 74;
    prog1.addChord(chChord(arr, 3));
    
    // Em
    arr[0] = 64;
    arr[1] = 67;
    arr[2] = 71;
    prog1.addChord(chChord(arr, 3));
    
    // Am
    arr[0] = 69;
    arr[1] = 72;
    arr[2] = 76;
    prog1.addChord(chChord(arr, 3));
    
    // Dm
    arr[0] = 74;
    arr[1] = 77;
    arr[2] = 81;
    prog1.addChord(chChord(arr, 3));
    
    // G
    arr[0] = 79;
    arr[1] = 83;
    arr[2] = 86;
    prog1.addChord(chChord(arr, 3));
    
    // C
    arr[0] = 72;
    arr[1] = 76;
    arr[2] = 79;
    prog1.addChord(chChord(arr, 3));
    
    // C7
    arr[0] = 72;
    arr[1] = 76;
    arr[2] = 79;
    arr[3] = 82;
    prog1.addChord(chChord(arr, 4));
    
    progression.push_back(prog1);
    
    for (size_t i = 0; i < progression.size(); i++) {
        for (size_t j = 0; j < progression[i].size(); j++) {
            std::cerr << progression[i].chords[j].chord.getFirstName() << ", ";
        }
        std::cerr << std::endl;
    }

    current_progression_indx = rand() % progression.size();
    current_progression_chord_indx = 0;
    
    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++) {
        
        curProgression.chords[i].x = (i+1) * 0.3;
        curProgression.chords[i].y = 0.5;
        
        curProgression.chords[i].currentx = (i+1) * 0.3 + 1.5;
        curProgression.chords[i].currenty = 0.5;
    }
    
    test.tmp_a = 255;
    test.width = test.height = 600;
    test.relx = 0.3;
    test.rely = 0.4;
}

void chPracticeScene::update() {
    arrow.move();
    arrow.move();
    arrow.move();
    arrow.move();
    arrow.move();
    arrow.move();
    arrow.move();
    arrow.move();
    if (arrow.tmp_a == 255) {
        arrow.a = 0;
    } else if (arrow.tmp_a == 0) {
        arrow.a = 255;
    }
    
    // Move chords
    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++) {
        curProgression.chords[i].move();
    }
    
    // Detect keydown
    vector<int> keydown = chAppState::instance()->midi->getKeys();
    chChord chord(keydown);
    vector<string> current_chords = chord.getNames();
    
    string expected_chord_name = curProgression.chords[current_progression_chord_indx].chord.getFirstName();
    
    bool same = false;
    for (size_t i = 0; i < current_chords.size(); i++) {
        if (current_chords[i] == expected_chord_name) {
            
            for (size_t i = 0; i < curProgression.size(); i ++) {
                curProgression.chords[i].x -= 0.3;
            }

            if (current_progression_chord_indx < curProgression.size() - 1) {
                current_progression_chord_indx ++;
            }
        }
    }
}

void chPracticeScene::draw() {
    // Background
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
//    test.drawCenter();
    arrow.drawCenter();
    
    // Progression
    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++){
        curProgression.chords[i].draw();
    }
}
