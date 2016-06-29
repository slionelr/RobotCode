/*
 * Robot.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#include <cmath>
#include "Robot.h"

#define M_PI_2 (2 * M_PI)

#define DEGREE_TOLERANCE 1
#define MOVE_TOLERANCE 0.1

// TODO: Check if the robot is going to get into the obstacle

Robot::Robot(const std::string ip, int port, Map grid) {
	_position = Position();
	pc = new PlayerCc::PlayerClient(ip, port);
	pp = new PlayerCc::Position2dProxy(pc, 0);
	lp = new PlayerCc::LaserProxy(pc, 0);
	_mngLocation = LocalizationManager(lp, LASER_COUNT, grid);

	_grid = grid;

	// We need this so that real robot will activate its motor
	pp->SetMotorEnable(true);
}

void Robot::SetOdometry(Position p) {
	_position = p;
	pp->SetOdometry(CM_TO_METER(p.x), AXIS_REDIRECT(CM_TO_METER(p.y)), p.o);
	_mngLocation.StartKnownPoint(p);
}

void Robot::Read() {
	pc->Read();
	// DO NOT DELETE THIS LOOP - FOR GARBAGE VALUES AT START
	while ((pp->GetXPos() == 0) && (pp->GetYPos() == 0) && (pp->GetYaw() == 0)) {
		pc->Read();
	}

#ifdef REAL
	double realO = pp->GetYaw();
	if (realO > M_PI) {
		realO = realO - M_PI_2;
	}
	_position = Position(METER_TO_CM(pp->GetXPos()),
						 AXIS_REDIRECT(METER_TO_CM(pp->GetYPos())),
						 realO);
#else
	_position = Position(METER_TO_CM(pp->GetXPos()),
						 AXIS_REDIRECT(METER_TO_CM(pp->GetYPos())),
						 pp->GetYaw());
#endif
}

void Robot::SetSpeed(double speed, double yaw) {
	pp->SetSpeed(speed, yaw);
}

void Robot::Stop() {
	SetSpeed(0,0);
}

Position Robot::GetPosition() {
	Read();
	return _position.Clone();
}

// TODO: Calculate it with SLAM/LocalizationManager
Position Robot::GetEstPosition() {
	return GetPosition();
}

bool Robot::MoveTo(Point dst) {
	double dx, dy, dO;
	Position pOld = _position.Clone();

	if (!RoteteTo(dst)) {
		// TODO: Error message
		std::cout << "Couldn't rotate to the destination point: " <<
					 "[X: " << dst.x << "] [Y: " << dst.y << "]" << std::endl;
		return false;
	}

	std::cout << "Starting Moving To: " <<
				 "[" << dst.x << "," << dst.y << "]" << std::endl;

	SetSpeed(0.06,0);
	while((_position.x < (dst.x - MOVE_TOLERANCE)) ||
		  (_position.x > (dst.x + MOVE_TOLERANCE)) ||
		  (_position.y < (dst.y - MOVE_TOLERANCE)) ||
		  (_position.y > (dst.y + MOVE_TOLERANCE))) {
		Read();
//		std::cout <<  "Current Position:[" << current.x << "," << current.y << "]" << std::endl;
		std::cout <<  "Current Position:[" << _position.x << "," << _position.y << "]" << std::endl;
	}
	Stop();

	std::cout << "Robot is Done Moving" << std::endl;

	// Calculate deltas
	dx = _position.x - pOld.x;
	dy = _position.y - pOld.y;
	dO = _position.o - pOld.o;

	// Update particles
	_mngLocation.Update(dx, dy, dO);
	return true;
}

bool Robot::RoteteTo(Point dst) {
	Position current = GetEstPosition();

	double degree = FindDegreeToRotate(current.GetPoint(), dst);
	double rotationSide = FindRotationSide(current.o, degree);

	double maxDegreeTolerance = degree + DEGREE_2_RAD(DEGREE_TOLERANCE);
	double minDegreeTolerance = degree - DEGREE_2_RAD(DEGREE_TOLERANCE);

	SetSpeed(0, rotationSide);
	while((GetEstPosition().o < minDegreeTolerance) || (GetEstPosition().o > maxDegreeTolerance)) {
//		Read();
		std::cout <<  "Robot:" << GetEstPosition().o << std::endl;
		Position c = GetEstPosition();
		c.Print();
	}
	Stop();

	return true;
}

void Robot::SaveParticles() {
	std::vector<Position> parti = _mngLocation.GetParticlesPosition();
	parti.push_back(_position);
	_grid.SaveToFile("particles.grid.png", parti);
}

void Robot::SaveParticles(Map map) {
	std::vector<Position> parti = _mngLocation.GetParticlesPosition();
	for (int i =0; i < parti.size(); i++) {
		parti[i] = map.ConvertLocation(parti[i]);
	}
	parti.push_back(map.ConvertLocation(_position));
	map.SaveToFile("particles.map.png", parti);
}

// Private Function
double Robot::FindDegreeToRotate(Point src, Point dst/*, double Yaw*/) {
//	double linearX;
//	double linearY;
//	int yaw;
	int linearX;
	int linearY;

	linearX = dst.x - src.x;
	linearY = -1 * (dst.y - src.y);
//	linearY = dst.y - src.y;
//	yaw = Yaw;

//	int linearXint = linearX * 10000;
//	int linearYint = linearY * 10000;
	int linearXint = linearX;
	int linearYint = linearY;

//	double degreeRobotToWaypoint = atan2(linearYint, linearXint) *  180 / M_PI;
	double degreeRobotToWaypoint = atan2(linearYint, linearXint);

	return degreeRobotToWaypoint;
}

double Robot::FindRotationSide(double srcYaw, double dstYaw)
{
	double leftCost = 0, rightCost = 0;

	if(srcYaw > 0)
	{
		if(dstYaw >= 0 && dstYaw < srcYaw)
		{
			leftCost = 180 - 20 + 180 + dstYaw;
			rightCost = srcYaw - dstYaw;
		}
		else if(dstYaw >= 0 && dstYaw >= srcYaw)
		{
			leftCost = dstYaw - srcYaw;
			rightCost = srcYaw + 180 + (180 -dstYaw);
		}
		else if(dstYaw < 0)
		{
			leftCost = 180 - srcYaw + (180 + dstYaw);
			rightCost = srcYaw + (-1 * dstYaw);
		}

	}
	else
	{
		if(dstYaw <= 0 && dstYaw < srcYaw)
		{
			leftCost = (-1 * srcYaw) + 180 + dstYaw;
			rightCost = (-1 * dstYaw) + srcYaw;
		}
		else if(dstYaw <= 0 && dstYaw >= srcYaw)
		{
			leftCost = (-1 * srcYaw) + dstYaw;
			rightCost = 180 + srcYaw + 180 + (-1 * dstYaw);
		}
		else if(dstYaw > 0)
		{
			leftCost = (-1 * srcYaw) + dstYaw;
			rightCost = 180 + srcYaw + (180 - dstYaw);
		}
	}


	if(leftCost < rightCost) {
		// Turn Left
		return 0.1;
	} else {
		// Turn Right
		return -0.1;
	}
}

Robot::~Robot() {
	// TODO: Disconnect
//	delete pc;
//	delete pp;
//	delete lp;
}

