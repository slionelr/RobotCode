/*
 * Robot.h
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <iostream>
#include <libplayerc++/playerc++.h>

#include "State.h"

class Robot {
private:
	PlayerCc::PlayerClient* pc;
	PlayerCc::Position2dProxy* pp;
	PlayerCc::LaserProxy* lp;
	State* sCurr;
public:
	Robot(const std::string ip, int port);
	void Read();
	void MoveTo(double speed, double yaw);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
