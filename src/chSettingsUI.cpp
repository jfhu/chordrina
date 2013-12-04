//
//  chSettingsUI.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/20/13.
//
//

#include "ofMain.h"
#include "chSettingsUI.h"
#include "chAppState.h"


chSettingScene::chSettingScene() {
    gui->setHeight(300);
    midi_choices.push_back("none"); // hackhack
    setup();
	ofAddListener(gui->newGUIEvent, this, &chSettingScene::guiEvent);
}

void chSettingScene::setup() {
    
    // Get a list of midi devices
    std::vector<std::string> current_midi_list = chAppState::instance()->midi->getPortList();
    bool midi_list_changed = false;
    if (midi_choices.size() != current_midi_list.size()) {
        midi_list_changed = true;
    } else {
        for (size_t i = 0; i < midi_choices.size(); i ++) {
            if (midi_choices[i] != current_midi_list[i]) {
                midi_list_changed = true;
            }
        }
    }
    
    // If the list of available midi devices is different from before... update the UI.
    if (midi_list_changed) {
        midi_choices = current_midi_list;
        
        // refresh gui
        gui->removeWidgets();
        gui->addLabel("Settings", OFX_UI_FONT_LARGE);
        gui->addSpacer();
        
        // Select Midi Input
        midi_choices = chAppState::instance()->midi->getPortList();
        string current_port_name = chAppState::instance()->midi->currentPortName;
        
        gui->addLabel("Select Midi Input", OFX_UI_FONT_MEDIUM);
        if (midi_choices.size() > 0) {
            ofxUIRadio * radio = gui->addRadio("MIDISelect", midi_choices, OFX_UI_ORIENTATION_VERTICAL);
            
            // If the current_port_name is not available anymore... pick the first one in the list
            if (std::find(midi_choices.begin(), midi_choices.end(), current_port_name) == midi_choices.end()) {
                chAppState::instance()->midi->currentPortName = midi_choices[0];
                if (chAppState::instance()->midi->currentPortName != current_port_name) {
                    current_port_name = chAppState::instance()->midi->currentPortName;
                    chAppState::instance()->midi->setPort(current_port_name);
                }
            }
            
            radio->activateToggle(current_port_name);
        }
        gui->addSpacer();
        
        gui->addLabelButton("Next Chord", "BtnNextChord")
        ->setColorBack(ofxUIColor(0));
        
        gui->addSpacer();
        
        gui->addLabelButton("Learn Chord", "LearningScene")->setColorBack(ofxUIColor(0));
        gui->addLabelButton("Learn Progression", "PracticeScene")->setColorBack(ofxUIColor(0));
        gui->addLabelButton("Play A Song", "SongScene")->setColorBack(ofxUIColor(0));
    }
}

void chSettingScene::draw() {
    static int counter = 0;
    if (++counter > 60) { // Detect new midi devices every second
        counter = 0;
        setup();

    }
    //    ofPushStyle();
    //    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //    ofPopStyle();
}

extern std::string chordList[];
extern std::string qualityList[];
void chSettingScene::guiEvent(ofxUIEventArgs &e) {
    std::string name = e.widget->getName();
  	int kind = e.widget->getKind();
//    std::cerr << name << " " << kind << std::endl;
    
    if (kind == OFX_UI_WIDGET_TOGGLE) {
        ofxUIToggle * toggle = e.getToggle();
        ofxUIRadio * radio = (ofxUIRadio*) toggle->getParent();
        if (radio->getName() == "MIDISelect") {
            ofLogNotice() << "setting: " << "Switched midi input to " << toggle->getName();
            chAppState::instance()->midi->setPort(toggle->getName());
        }
    } else if (kind == OFX_UI_WIDGET_LABELBUTTON) {
        ofxUIButton * button = e.getButton();
        if (button->getValue() != 1) {
            return;
        }
        
        if (name == "Next Chord") {
            std::string rand_chord = chordList[rand() % 12];
            std::string rand_quality = qualityList[rand() % 5];
            chAppState::instance()->current_chord = rand_chord + " " + rand_quality;
        } else if (name == "Learn Chord") {
            chAppState::instance()->current_scene_type = SCENE_LEARN;
        } else if (name == "Learn Progression") {
            chAppState::instance()->current_scene_type = SCENE_PRACTICE;
        } else if (name == "Play A Song") {
            chAppState::instance()->current_scene_type = SCENE_PLAY;
        }
        
        
    }
}