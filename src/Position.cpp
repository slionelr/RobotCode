/*
 * Position.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#include <iostream>
#include "Position.h"

void Position::init(int x, int y, double o) {
	this->x = x;
	this->y = y;
	this->o = o;
}

Position::Position() {
	init(0,0,0);
}

Position::Position(int x, int y) {
	init(x,y,0);
}

Position::Position(int x, int y, double o) {
	init(x,y,o);
}

Point Position::GetPoint() {
	Point p = Point(this->x, this->y);
	return p;
}

Position Position::Clone() {
	return Position(this->x, this->y, this->o);
}

void Position::Print() {
	std::cout << "[X: " << this->x << " ]"
			  << "[Y: " << this->y << " ]"
			  << "[O: " << this->o << " ]";
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

