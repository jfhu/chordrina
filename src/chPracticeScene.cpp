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
    chProgressionChord::font->loadFont("Fonts/Cutie Patootie.ttf", 10);
    
    bgImg.tmp_a = 255;
    
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

    chProgression& curProgression = progression[current_progression_indx];
    for (size_t i = 0; i < curProgression.size(); i ++) {
        
        curProgression.chords[i].x = (i+1) * 0.3;
        curProgression.chords[i].y = 0.5;
        
        curProgression.chords[i].currentx = (i+1) * 0.3 + 1.5;
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
    
//    test.r = 255; test.g = 185; test.b = 20;
    test.drawCenter();
}