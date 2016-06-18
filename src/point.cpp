/*
 * point.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#include <iostream>

#include "Point.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

void Point::Print() {
	std::cout << "[X: " << this->x << "] [Y: " << this->y << "]" << std::endl;
}
