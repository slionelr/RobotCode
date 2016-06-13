/*
 * State.h
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#ifndef STATE_H_
#define STATE_H_

class State {
public:
	// Properties
	double x;
	double y;
	double o;
	// Funcs
	State();
	State(double x, double y, double o);
	State* Clone();
	virtual ~State();
};

#endif /* STATE_H_ */
