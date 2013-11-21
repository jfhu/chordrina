//
//  chMidiListener.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#include "chMidiListener.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

void chMidiListener::setup() {
    midiIn->ignoreTypes(false, false, false);
    midiIn->listPorts();
    std::vector<std::string> & port_list = midiIn->getPortList();
    if (port_list.size()) {
        setPort(port_list[0]);
    }
    midiIn->addListener(this);
    midiIn->setVerbose(true);
}

void chMidiListener::exit() {
    midiIn->closePort();
    midiIn->removeListener(this);
}

std::vector<std::string> & chMidiListener::getPortList() {
    return midiIn->getPortList();
}

void chMidiListener::setPort(std::string portName) {
    ofLogNotice() << "midiListener: " << "Setting port to " << portName;
    midiIn->closePort();
    midiIn->openPort(portName);
    currentPortName = portName;
}

void chMidiListener::newMidiMessage(ofxMidiMessage& msg) {
    ofLogNotice() << "midiListener: " << msg.pitch << " " << msg.velocity << " " <<
        msg.control << " " << msg.value << " " << msg.deltatime;
    
    if (msg.velocity == 0) {
        keydown.erase(std::remove(keydown.begin(), keydown.end(), msg.pitch), keydown.end());
    } else {
        keydown.push_back(msg.pitch);
    }

    std::stringstream out;
    out << msg.pitch;
    keys = out.str();
}

std::vector<int> chMidiListener::getKeys() {
    return keydown;
}

