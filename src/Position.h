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
	void init(signed x, signed y, signed o);
public:
	signed _x;
	signed _y;
	signed _o;
	Position();
	Position(signed x, signed y);
	Position(signed x, signed y, signed o);
	virtual ~Position();
	void Print();
};

#endif /* POSITION_H_ */
