/*
 * State.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#include "State.h"

State::State() {
	State::State(0,0,0);
}

State::State(double x, double y, double o) {
	// TODO Auto-generated constructor stub
}

State* State::Clone() {
	return new State::State(x, y, o);
}

State::~State() {
	// TODO Auto-generated destructor stub
}
