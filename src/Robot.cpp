/*
 * Robot.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(const std::string ip, int port) {
	sCurr = new State();
	pc = new PlayerCc::PlayerClient(ip, port);
	pp = new PlayerCc::Position2dProxy(pc, 0);
	lp = new PlayerCc::LaserProxy(pc, 0);
}

void Robot::Read() {
	State* sOld = sCurr->Clone();
	double dx, dy;

	pc->Read();

	// Set current position
	sCurr->x = pp->GetXPos();
	sCurr->y = pp->GetYPos();
	sCurr->o = pp->GetYaw();

	// Calculate deltas
	dx = sCurr->x - sOld->x;
	dy = sCurr->y - sOld->y;
	// Do we need DeltaYaw?

	delete sOld;
}

void Robot::MoveTo(double speed, double yaw) {
	pp->SetSpeed(speed, yaw);
}

Robot::~Robot() {
	// TODO: Disconnect
	delete sCurr;
	delete pc;
	delete pp;
	delete lp;
}
