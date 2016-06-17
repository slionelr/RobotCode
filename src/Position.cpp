/*
 * Position.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#include <iostream>
#include "Position.h"

void Position::init(float x, float y, float o) {
	this->x = x;
	this->y = y;
	this->o = o;
}

Position::Position() {
	init(0,0,0);
}

Position::Position(float x, float y) {
	init(x,y,0);
}

Position::Position(float x, float y, float o) {
	init(x,y,o);
}

Point Position::GetPoint() {
	return Point(
			this->x,
			this->y);
}

Position Position::Clone() {
	return Position(this->x, this->y, this->o);
}

void Position::Print() {
	std::cout << "[X: " << this->x << " ]"
			  << "[Y: " << this->y << " ]"
			  << "[O: " << this->o << " ]" << std::endl;
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

