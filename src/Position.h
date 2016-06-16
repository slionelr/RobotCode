/*
 * Position.h
 *
 *  Created on: Jun 14, 2016
 *      Author: user
 */

#ifndef POSITION_H_
#define POSITION_H_


class Position {
private:
	void init(float x, float y, float o);
public:
	double x;
	double y;
	double o;
	Position();
	Position(float x, float y);
	Position(float x, float y, float o);
	Position Clone();
	void Print();
	virtual ~Position();
};

#endif /* POSITION_H_ */
