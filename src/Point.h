/*
 * Point.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point() {}
	Point(unsigned x, unsigned y);
	unsigned GetX();
	unsigned GetY();
	unsigned x;
	unsigned y;
};

#endif /* POINT_H_ */
