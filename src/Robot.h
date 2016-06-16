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

#include "Position.h"
#include "LocalizationManager.h"

#define LASER_COUNT 666

class Robot {
private:
	PlayerCc::PlayerClient* pc;
	PlayerCc::Position2dProxy* pp;
	PlayerCc::LaserProxy* lp;
	Position _position;
	LocalizationManager _mngLocation;
public:
	Robot(const std::string ip, int port, Map map);
	void Read();
	void SetSpeed(double speed, double yaw);
	Position GetPosition();
	void SaveParticles();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
