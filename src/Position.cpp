/*
 * Position.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#include "Position.h"

Position::Position() {
	Position(0,0,0);
}

Position::Position(signed x, signed y) {
	Position(x,y,0);
}

Position::Position(signed x, signed y, signed o) {
	_x = x;
	_y = y;
	_o = o;
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}
