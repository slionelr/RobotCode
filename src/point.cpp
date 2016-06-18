/*
 * point.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#include "Point.h"

Point::Point(unsigned x, unsigned y) {
	this->x = x;
	this->y = y;
}

void Point::Print() {
	std::cout << "[X: " << this->x << "] [Y: " << this->y << "]" << std::endl;
}
