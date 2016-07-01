/*
 * Point.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef POINT_H_
#define POINT_H_

#include "World.h"

class Point {
public:
	int x;
	int y;
	Point() {}
	Point(int x, int y);
	void Print();
};

#endif /* POINT_H_ */
