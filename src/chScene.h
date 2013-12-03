//
//  chScene.h
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#ifndef __chordrina__chScene__
#define __chordrina__chScene__

#include <iostream>
#include "ofMain.h"

enum SCENE {
	SCENE_MENU,
	SCENE_LEARN,
	SCENE_PRACTICE,
	SCENE_PLAY
};


class chScene {
public:
    virtual void update() {};
    virtual void setup() {};
	virtual void draw() = 0;
};


class chMenuScene : public chScene {
public:
	virtual void draw();
};

#include "chLearningScene.h"
#include "chSettingsUI.h"
#include "chPracticeScene.h"
#include "chPlayScene.h"

#endif /* defined(__chordrina__chScene__) */
