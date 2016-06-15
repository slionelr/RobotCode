/*
 * Particle.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */
#include <cmath>

#include "Particle.h"

Particle::Particle(double x, double y, double o) {
	this->position.x = x;
	this->position.y = y;
	this->position.o = o;
	// TODO: Change the stating belif value (maybe need to get it from the constructor)
	this->belif = 0; // !!!!!
}

void Particle::Update(double* arrLaser, int laserLen, double dx, double dy, double dO, Map map) {
	double preBelif;

	// Update the particle position using the delta values
	position.x = position.x + dx;
	position.y = position.y + dy;
	position.o = position.o + dO;

	// Get the predictable belif
	preBelif = belif * ProbByMov(dx, dy, dO);
	// Get the NEW belif
	belif = NORMAL * preBelif * ProbByLaser(arrLaser, laserLen, map);
}

double Particle::ProbByMov(double dx, double dy, double dO) {
	double d = pow(dx, 2) + pow(dy, 2);
	d = sqrt(d);

	// TODO: Return the probability to get to the destination
	if (d < 0.2 && dO < 2) {
		return 1;
	} else if (true){
		return 0.0;
	} else {
		return 0.0;
	}
}

double Particle::ProbByLaser(double* arrLaser, int laserLen, Map map) {
	return 0.0;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}
