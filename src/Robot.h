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
	Map _grid;
	void Read();
	double FindRotationSide(double srcYaw, double dstYaw);
	double FindDegreeToRotate(Point src, Point dst/*, double Yaw*/);
public:
	Robot(const std::string ip, int port, Map grid);
	void SetOdometry(Position p);
	void SetSpeed(double speed, double yaw);
	void Stop();
	Position GetPosition();
	Position GetEstPosition();
	Position GetPositionOnGrid();
	bool MoveTo(Point dst);
	bool RoteteTo(Point dst);
	void SaveParticles();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
