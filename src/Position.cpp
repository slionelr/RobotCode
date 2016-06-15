/*
 * Position.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#include <iostream>
#include "Position.h"

void Position::init(signed x, signed y, signed o) {
	this->x = x;
	this->y = y;
	this->o = o;
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

Position Position::Clone() {
	return Position(this->x, this->y, this->o);
}

void Position::Print() {
	std::cout << "[X: " << this->x << " ][Y: " << this->y << "]" << std::endl;
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

