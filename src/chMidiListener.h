//
//  chMidiListener.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#ifndef __chordrina__chMidiListener__
#define __chordrina__chMidiListener__

#include <iostream>
#include <vector>
#include "ofMain.h"
#include "ofxMidi.h"


class chMidiListener : public ofxMidiListener {
public:
    void setup();
    void exit();

    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    std::vector<std::string> & getPortList();
//    void setPort(std::string portName);
    std::string currentPortName = "";
    
    std::vector<int> getKeys();

private:
    ofxMidiIn * midi = new ofxMidiIn();
    std::vector<ofxMidiIn *> midiIns;

    std::vector<int> keydown;
};

#endif /* defined(__chordrina__chMidiListener__) */
