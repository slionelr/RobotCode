/*
 * Particle.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */
#include <cmath>

#include "Particle.h"

//Particle::Particle() {
//	init(0,0,0,Map());
//}

Particle::Particle(double x, double y, double o, Map map) {
	init(x,y,o,map);
}

void Particle::init(double x, double y, double o, Map map) {
	this->position.x = x;
	this->position.y = y;
	this->position.o = o;
	this->_map = map;
	// TODO: Change the stating belif value (maybe need to get it from the constructor)
	this->belif = 1.0; // !!!!!
}

void Particle::Update(double* arrLaser, int lasersLen, double dx, double dy, double dO) {
	// If the robot doesnt move than exit
	if((dx == 0) && (dy == 0) && (dO == 0)) {
		return;
	}

	// Update the particle position using the delta values
	position.x = position.x + dx;
	position.y = position.y + dy;
	position.o = position.o + dO;

	// Get the predictable belif
	double preBelif = belif * ProbByMov(dx, dy, dO);
	// Get the NEW belif
	double probLasers = ProbByLaser(arrLaser, lasersLen);
	belif = NORMAL * preBelif * probLasers;
}

double Particle::ProbByMov(double dx, double dy, double dO) {
	double probO = 1.0;

	double d = pow(dx, 2) + pow(dy, 2);
	d = sqrt(d);

	if (dO != 0) {
		probO = (M_PI - dO) / M_PI;
	}

	// TODO: Do some probabilty calculation for distance
	return probO;
}

double Particle::ProbByLaser(double* arrLaser, int lasersLen) {
	const double MAX_LASER_DISTANCE = 40.0;
	double misCounter = 0;
	double mr_Counter = 0;

	for (int i=0; i < lasersLen; i++) {
		double obsDistance = arrLaser[i];

		// If there is an object in-front of this laser than score it
		if (obsDistance < MAX_LASER_DISTANCE && obsDistance > 0.0) {
			double lsrAngle = GetLaserAngle(i, lasersLen);
			double mapAngle = position.o + lsrAngle;

			double x = obsDistance * cos(mapAngle);
			double y = obsDistance * sin(mapAngle);

			x = METER_TO_CM(x);
			y = AXIS_REDIRECT(METER_TO_CM(y));

			x = x + position.x;
			y = y + position.y;

			if ((x < 0.0) || (x > _map.GetWidth()) ||
				(y < 0.0) || (y > _map.GetHeight())) {
				misCounter++;
			} else {
				int value = _map.GetValue(y, x);
				if (value) {
					mr_Counter++;
				} else {
					misCounter++;
				}
			}
		}
	}

	if ((misCounter + mr_Counter) == 0) {
		return 1.0;
	} else {
		return mr_Counter / (misCounter + mr_Counter);
	}
}

double Particle::GetLaserAngle(int index, int lasersLen) {
	// range-of-lasers(240) / resolution(0.36) => 666 samples <=> _laserLen
	return DEGREE_2_RAD((LASER_RESOLUTION * index) - (((double)lasersLen * LASER_RESOLUTION) / 2.0));
}

int Particle::operator==(const Particle &r) {
	return ((position.x == r.position.x) &&
			(position.y == r.position.y));
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}
