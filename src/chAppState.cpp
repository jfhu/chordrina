//
//  chAppState.cpp
//  chordrina
//
//  Created by Jianfeng Hu on 11/17/13.
//
//

#include "chAppState.h"
#include <iostream>

chAppState * chAppState::m_instance = NULL;

chAppState * chAppState::instance() {
	if (!m_instance) {
		m_instance = new chAppState();
	}
	return m_instance;
}
