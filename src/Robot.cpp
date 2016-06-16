/*
 * Robot.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(const std::string ip, int port, Map map) {
	_position = Position();
	pc = new PlayerCc::PlayerClient(ip, port);
	pp = new PlayerCc::Position2dProxy(pc, 0);
	lp = new PlayerCc::LaserProxy(pc, 0);
	_mngLocation = LocalizationManager(lp, LASER_COUNT, map);

	// We need this so that real robot will activate its motor
	pp->SetMotorEnable(true);
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

Position Robot::GetPosition() {
	return Position(
			pp->GetXPos(),
			pp->GetYPos(),
			pp->GetYaw()
			);
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
