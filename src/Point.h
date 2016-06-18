/*
 * Point.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point {
public:
	unsigned x;
	unsigned y;
	Point() {}
	Point(unsigned x, unsigned y);
	void Print();
};

#endif /* POINT_H_ */
