//
//  chMidiListener.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#include "chMidiListener.h"
#include "chAppState.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

void chMidiListener::setup() {
    // cleanup
    for (size_t i = 0; i < midiIns.size(); i ++) {
        midiIns[i]->closePort();
        midiIns[i]->removeListener(this);
    }
    
    // get device list
    std::vector<std::string> & port_list = midi->getPortList();
    
    // create rtMidi instances
    for (size_t i = 0; i < port_list.size(); i ++) {
        ofxMidiIn * midiIn = new ofxMidiIn();
        midiIn->ignoreTypes();
        midiIn->addListener(this);
        midiIn->setVerbose(true);
        midiIn->openPort(port_list[i]);
        midiIns.push_back(midiIn);
    }
}

void chMidiListener::exit() {
    for (size_t i = 0; i < midiIns.size(); i ++) {
        midiIns[i]->closePort();
        midiIns[i]->removeListener(this);
    }
}

std::vector<std::string> & chMidiListener::getPortList() {
    return midi->getPortList();
}

//void chMidiListener::setPort(std::string portName) {
//    return;
//    
//    
//    ofLogNotice() << "midiListener: " << "Setting port to " << portName;
//    midiIn->closePort();
//    midiIn->openPort(portName);
//    currentPortName = portName;
//}

void forwardMidiMessageToSynth(ofxMidiMessage& msg) {
    chSynth * synth = chAppState::instance()->synth;
    if (!synth)
        return;
    switch (msg.status) {
        case MIDI_NOTE_OFF:
            synth->noteOff(msg.channel, msg.pitch);
            break;
        case MIDI_NOTE_ON:
            synth->noteOn(msg.channel, msg.pitch, msg.velocity);
            break;
        case MIDI_CONTROL_CHANGE:
            synth->controlChange(msg.channel, msg.control, msg.value);
            break;
        case MIDI_PROGRAM_CHANGE:
            synth->programChange(msg.channel, msg.value);
            break;
        case MIDI_PITCH_BEND:
            synth->pitchBend(msg.channel, msg.value);
            break;
        case MIDI_AFTERTOUCH:
            ofLogNotice() << "midiListener: " << "aftertouch ignored";
            break;
        case MIDI_POLY_AFTERTOUCH:
            ofLogNotice() << "midiListener: " << "poly-aftertouch ignored";
            break;
        default:
            ;
//            ofLogNotice() << "midiListener: " << "unknown midi status " << msg.status;
    }
}


void chMidiListener::newMidiMessage(ofxMidiMessage& msg) {
    
    // hackhack
    if (msg.status == MIDI_NOTE_ON && msg.velocity == 0) {
        msg.status = MIDI_NOTE_OFF;
    }

    ofLogNotice() << "midiListener: " << msg.toString() << msg.pitch;

    // Play every channel
    forwardMidiMessageToSynth(msg);

    // Only remember channel 1 for keydowns
    if (msg.channel == 1) {
        if (msg.velocity == 0) {
            keydown.erase(std::remove(keydown.begin(), keydown.end(), msg.pitch), keydown.end());
        } else {
            keydown.push_back(msg.pitch);
        }
    }

}


std::vector<int> chMidiListener::getKeys() {
    std::sort(keydown.begin(), keydown.end());
    return keydown;
}
