//
//  chImage.h
//  chordrina
//
//  Created by Jianfeng Hu on 12/3/13.
//
//

#ifndef __chordrina__chImage__
#define __chordrina__chImage__

#include <iostream>
#include <map>
#include <string>
#include "ofMain.h"

class chImageBank {
public:
    static std::map<std::string, ofImage*> images;
    static ofImage * getImage(std::string name);
    static ofImage * loadImage(std::string name, std::string filename);
};


class chImage {
public:
    double relx = ofRandom(0, 1), rely = ofRandom(0, 1);
    double dx = 0, dy = 0;
    double width = 50, height = 50;
    int r = 255, g = 255, b = 255, a = 255;
    int tmp_a = 0; // for fade in. tmp_a is the current alpha, and a is the target alpha.
    double fade_duration = 600; // millisecond
    
    chImage(std::string name, std::string filename);
    
    void draw();
    void draw(double x, double y, double width, double height);
    void drawCenter();
    void move();
    
protected:
    ofImage * img;
};

#endif /* defined(__chordrina__chImage__) */
