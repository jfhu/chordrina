//
//  chImage.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 12/3/13.
//
//

#include "chImage.h"
#include <cstdlib>

using namespace std;

std::map<std::string, ofImage*> chImageBank::images;

ofImage* chImageBank::getImage(string name) {
    return images[name];
}

ofImage* chImageBank::loadImage(string name, string filename) {
    if (images.find(name) == images.end()) {
        images[name] = new ofImage(filename);
    }
    return images[name];
}

chImage::chImage(string name, string filename) {
    img = chImageBank::loadImage(name, filename);
}

void chImage::draw() {
    double w = ofGetWidth();
    double h = ofGetHeight();
    draw(relx*w, rely*h, width, height);
}

void chImage::drawCenter() {
    double w = ofGetWidth();
    double h = ofGetHeight();
    draw(relx*w-width/2.0, rely*h-height/2.0, width, height);
}

void chImage::draw(double x, double y, double width, double height) {
    ofSetColor(r, g, b, tmp_a);
    img->draw(x, y, width, height);
}

void chImage::move() {
    relx += dx/ofGetHeight();
    rely += dy/ofGetWidth();
//    ???
//    int dif = (a - tmp_a) / (1 / 60.0 / (fade_duration / 1000.0));
//    std::cerr << a << " " << tmp_a << " " << dif << std::endl;
    if (a > tmp_a) {
        tmp_a += 1;
    } else if (a < tmp_a) {
        tmp_a -= 1;
    }
}
