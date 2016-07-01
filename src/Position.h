/*
 * Position.h
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "World.h"
#include "Point.h"

#define DEGREE_2_RAD(d) (d * M_PI / 180)
#define RAD_2_DEGREE(r) (r / M_PI * 180)

class Position {
private:
	void init(int x, int y, double o);
public:
	int x;
	int y;
	double o;
	Position();
	Position(int x, int y);
	Position(int x, int y, double o);
	Point GetPoint();
	Position Clone();
	void Print();
	virtual ~Position();
};

#endif /* POSITION_H_ */
