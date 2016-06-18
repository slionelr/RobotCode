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

//unsigned Point::GetX() {
//	return this->x;
//}
//
//unsigned Point::GetY() {
//	return this->y;
//}

void Point::Print() {
	std::cout << "[X: " << this->x << "] [Y: " << this->y << "]" << std::endl;
}
