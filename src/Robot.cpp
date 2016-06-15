/*
 * Robot.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(const std::string ip, int port) {
	position = Position();
	pc = new PlayerCc::PlayerClient(ip, port);
	pp = new PlayerCc::Position2dProxy(pc, 0);
	lp = new PlayerCc::LaserProxy(pc, 0);
}

void Robot::Read() {
	Position pOld = position.Clone();
	double dx, dy;

	pc->Read();

	// Set current position
	position.x = pp->GetXPos();
	position.y = pp->GetYPos();
	position.o = pp->GetYaw();

	double d = lp->GetRange(333);
	std::cout << d << std::endl;

	// Calculate deltas
	dx = position.x - pOld.x;
	dy = position.y - pOld.y;
	// Do we need DeltaYaw?
}

void Robot::SetSpeed(double speed, double yaw) {
	pp->SetSpeed(speed, yaw);
}

Robot::~Robot() {
	// TODO: Disconnect
//	delete pc;
//	delete pp;
//	delete lp;
}
