/*
 * point.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#include "Point.h"

Point::Point(unsigned x, unsigned y) {
	_x = x;
	_y = y;
}

unsigned Point::GetX() {
	return _x;
}

unsigned Point::GetY() {
	return _y;
}
