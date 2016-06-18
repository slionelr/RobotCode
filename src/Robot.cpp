/*
 * Robot.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#include "Robot.h"

#define METER_TO_CM(m) (m * 10)
#define CM_TO_METER(cm) (cm / 10)

#define DEGREE_TOLERANCE 1
#define MOVE_TOLERANCE 0.1

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
//	pp->SetOdometry(p.x, p.y, p.o);
	pp->SetOdometry(CM_TO_METER(p.x), -1 * CM_TO_METER(p.y), DEGREE_2_RAD(p.o));
}

void Robot::Read() {
	double dx, dy, dO;
	Position pOld = _position.Clone();

	pc->Read();

	// TODO: Set current position - we need to base our position on something else
	_position.x = pp->GetXPos();
	_position.y = pp->GetYPos();
	_position.o = pp->GetYaw();

	// Calculate deltas
	dx = _position.x - pOld.x;
	dy = _position.y - pOld.y;
	dO = _position.o - pOld.o;

	// Update particles
	_mngLocation.Update(dx, dy, dO);
}

void Robot::SetSpeed(double speed, double yaw) {
	pp->SetSpeed(speed, yaw);
}

void Robot::Stop() {
	SetSpeed(0,0);
}

Position Robot::GetPosition() {
	Read();
	while (pp->GetXPos() == 0 && pp->GetYPos() == 0 && pp->GetYaw() == 0) {
		Read();
	}
	Position p = Position(
			METER_TO_CM(pp->GetXPos()),
			METER_TO_CM(pp->GetYPos()) * -1,
//			METER_TO_CM(pp->GetYPos()),

//			pp->GetXPos(),
//			pp->GetYPos(),

			pp->GetYaw()
			);

	return p;
}

// TODO: Calculate it with SLAM/LocalizationManager
Position Robot::GetEstPosition() {
	return GetPosition();
}

Position Robot::GetPositionOnGrid() {
	Position est = GetEstPosition();
	Position onGrid = _grid.ConvertLocation(est);
	return onGrid;
}

bool Robot::MoveTo(Point dst) {
	if (!RoteteTo(dst)) {
		// TODO: Error message
		std::cout << "Couldn't rotate to the destination point: " <<
					 "[X: " << dst.x << "] [Y: " << dst.y << "]" << std::endl;
		return false;
	}

	std::cout << "Starting Moving To: " <<
				 "[" << dst.x << "," << dst.y << "]" << std::endl;

	SetSpeed(0.06,0);
	Position current = GetPositionOnGrid();
	while((current.x < (dst.x - MOVE_TOLERANCE)) ||
		  (current.x > (dst.x + MOVE_TOLERANCE)) ||
		  (current.y < (dst.y - MOVE_TOLERANCE)) ||
		  (current.y > (dst.y + MOVE_TOLERANCE))) {
//		Read();
		current = GetPositionOnGrid();
		std::cout <<  "Current Position:[" << current.x << "," << current.y << "]" << std::endl;
	}
	Stop();

	std::cout << "Robot is Done Moving" << std::endl;
	return true;
}

bool Robot::RoteteTo(Point dst) {
	Position current = GetPositionOnGrid();

	double degree = FindDegreeToRotate(current.GetPoint(), dst);
	double rotationSide = FindRotationSide(current.o, degree);

	double maxDegreeTolerance = degree + DEGREE_2_RAD(DEGREE_TOLERANCE);
	double minDegreeTolerance = degree - DEGREE_2_RAD(DEGREE_TOLERANCE);

	SetSpeed(0, rotationSide);
	while((GetPositionOnGrid().o < minDegreeTolerance) || (GetPositionOnGrid().o > maxDegreeTolerance)) {
//		Read();
		std::cout <<  "Robot:" << GetPositionOnGrid().o << std::endl;
		Position c = GetPositionOnGrid();
		c.Print();
	}
	Stop();

	return true;
}

void Robot::SaveParticles() {
	_mngLocation.PaticlesImage();
}

Robot::~Robot() {
	// TODO: Disconnect
//	delete pc;
//	delete pp;
//	delete lp;
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
