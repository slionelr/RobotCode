/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#include <stdlib.h>
#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map grid) {
	//_particles(); // Already initialized at declaration
	_lp = arrLaser;
	_lasersLen = lasersLen;
	_lasersData = (double*)malloc(lasersLen * sizeof(double));
	_map = grid;
}

void LocalizationManager::StartKnownPoint(Position start) {
	_particles.clear();
	for (int i=0; i < 15; i++) {
		Position pr = AddRandomParticle(start);
		_particles.push_back(Particle(pr.x, pr.y, pr.o));
	}
}

Position LocalizationManager::AddRandomParticle(Position p) {
	// TODO: deltaRand - Maybe reasonable that this will be at least 4 because of the resolution between map and grid
	const int deltaRand = 4;
	int randDeltaX, randDeltaY;
	double randDeltaO;
	int isNegative;

	// Random X
	isNegative = rand() % 2;
	randDeltaX = rand() % deltaRand;
	if (isNegative) {
		randDeltaX = randDeltaX * (-1);
	}

	// Random Y
	isNegative = rand() % 2;
	randDeltaY = rand() % deltaRand;
	if (isNegative) {
		randDeltaY = randDeltaY * (-1);
	}

	// Random Yaw
	isNegative = rand() % 2;
//	randDeltaO = ((double)(rand() % (int)(M_PI * 100))) / 100;
	randDeltaO = ((double)(rand() % (int)(DEGREE_2_RAD(10) * 100))) / 100;
	if (isNegative) {
		randDeltaO = randDeltaO * (-1);
	}

	Position ret = Position(p.x + randDeltaX,
							p.y + randDeltaY,
							p.o + randDeltaO);
	return ret;
}

void LocalizationManager::Update(double dx, double dy, double dO) {
	int index;
	for (index=0; index < _lasersLen; index++) {
		_lasersData[index] = _lp->GetRange(index);
	}

	for (index=0; index < _particles.size(); index++) {
		_particles[index].Update(_lasersData, _lasersLen, dx, dy, dO, _map);
	}
}

void LocalizationManager::AddParticle(Particle p) {
	if (_particles.size() < MAX_PARTICLES) {
		_particles.push_back(p);
	}
}

void LocalizationManager::RemoveParticle(Particle p) {
	unsigned index;
	for (index=0; index < _particles.size(); index++) {
		if (_particles[index] == p) {
			break;
		}
	}
	_particles.erase(_particles.begin() + index);
}

Map LocalizationManager::GetMap() {
	return this->_map;
}

std::vector<Position> LocalizationManager::GetParticlesPosition() {
	std::vector<Position> v;
	for (int i=0; i < _particles.size(); i++) {
		v.push_back(_particles[i].position);
	}
	return v;
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}
