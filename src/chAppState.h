//
//  chAppState.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#ifndef __chordrina__chAppState__
#define __chordrina__chAppState__

#include <iostream>
#include <string>
#include "chMidiListener.h"
#include "chScene.h"

class chAppState {
public:
	static chAppState * instance();

	// some global stuff
	chMidiListener * midi = new chMidiListener();
	bool should_show_debug = true;
	bool should_show_setting = true;
	SCENE current_scene = SCENE_LEARN;
    std::string current_chord = "A Maj";

private:
	chAppState() {
		midi->setup();
	};
	chAppState(chAppState const&) {};
	static chAppState * m_instance;

	// App state

};

#endif /* defined(__chordrina__chAppState__) */
