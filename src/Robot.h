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

#include "World.h"
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
	double offsetX;
	double offsetY;
	double offsetO;
public:
	Robot(const std::string ip, int port, Map grid, Map map);
	void SetOdometry(Position p);
	void SetSpeed(double speed, double yaw);
	void Stop();
	Position GetPosition();
	Position GetEstPosition();
	bool MoveTo(Point dst);
	bool RoteteTo(Point dst);
	void SaveParticles();
	void SaveParticles(Map map);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
