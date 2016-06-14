/*
 * Position.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#include <iostream>
#include "Position.h"

void Position::init(signed x, signed y, signed o) {
	_x = x;
	_y = y;
	_o = o;
}

Position::Position() {
	init(0,0,0);
}

Position::Position(signed x, signed y) {
	init(x,y,0);
}

Position::Position(signed x, signed y, signed o) {
	init(x,y,o);
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

void Position::Print() {
	std::cout << "[X: " << _x << " ][Y: " << _y << "]" << std::endl;
}
