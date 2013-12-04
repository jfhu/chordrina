//
//  chPracticeScene.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#include "chPracticeScene.h"

ofxTrueTypeFontUC * chProgressionChord::font = new ofxTrueTypeFontUC();


void chProgression::addChord(const chChord & chord) {
    chProgressionChord c(chord);
    chords.push_back(c);
}

void chPracticeScene::setup() {
    chProgressionChord::font->loadFont("Fonts/Cutie Patootie.ttf", 20);
    
    bgImg.tmp_a = 255;
    
    // Progressions TODO: read them from midi file
    int arr[5] = {0};
    chProgression prog1;
    
    arr[0] = 65;
    arr[1] = 69;
    arr[2] = 72;
    prog1.addChord(chChord(arr, 3));
    
    arr[0] = 67;
    arr[1] = 71;
    arr[2] = 74;
    prog1.addChord(chChord(arr, 3));
    
    arr[0] = 64;
    arr[1] = 67;
    arr[2] = 71;
    prog1.addChord(chChord(arr, 3));
    
    arr[0] = 69;
    arr[1] = 72;
    arr[2] = 76;
    prog1.addChord(chChord(arr, 3));
    
    progression.push_back(prog1);
    
    for (size_t i = 0; i < progression.size(); i++) {
        for (size_t j = 0; j < progression[i].size(); j++) {
            std::cerr << progression[i].chords[j].chord.getFirstName() << ", ";
        }
        std::cerr << std::endl;
    }

    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++) {
        
        curProgression.chords[i].x = (i+1) * 0.2;
        curProgression.chords[i].y = 0.5;
        
        curProgression.chords[i].currentx = (i+1) * 0.2 + 1.5;
        curProgression.chords[i].currenty = 0.5;
    }
    
    
    test.tmp_a = 255;
    test.width = test.height = 400;
}

void chPracticeScene::update() {
    
    // Move chords
    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++) {
        curProgression.chords[i].move();
    }
}

void chPracticeScene::draw() {
    // Background
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    // Progression
    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++){
        curProgression.chords[i].draw();
    }
    
//    ofCircle(300, 200, 100);
    
    test.r = 255; test.g = 185; test.b = 20;
    test.drawCenter();
}