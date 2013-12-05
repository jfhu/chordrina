//
//  chLearningScene.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#ifndef __chordrina__chLearningScene__
#define __chordrina__chLearningScene__

#include "chScene.h"
#include "chImage.h"
#include <iostream>
#include <vector>

using namespace std;


class chLearningScene : public chScene {
public:
    virtual void update();
    virtual void setup();
	virtual void draw();
private:
    chImage bgImg = chImage("background", "Img/bg.jpg");
    chImage bgBubble = chImage("bubble", "Img/bubble.png");
    
    vector<chImage> bgDots;
    
    int best_score = 0;
    int current_score = 0;
    bool current_chord_correct = false;
    
    bool should_draw_green_ball = false;
    string should_draw_text = "";
    double last_correct_time = 0;
};

#endif /* defined(__chordrina__chLearningScene__) */
