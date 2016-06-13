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
	signed _x;
	signed _y;
	signed _o;
public:
	Position();
	Position(signed x, signed y);
	Position(signed x, signed y, signed o);
	virtual ~Position();
};

#endif /* POSITION_H_ */
