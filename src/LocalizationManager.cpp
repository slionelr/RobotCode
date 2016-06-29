/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#include <stdlib.h>
#include <stdexcept>
#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map map) {
	//_particles(); // Already initialized at declaration
	_lp = arrLaser;
	_lasersLen = lasersLen;
	_lasersData = (double*)malloc(lasersLen * sizeof(double));
	_map = map;
}

void LocalizationManager::StartKnownPoint(Position start) {
	_particles.clear();

	// Add robot start position
	_particles.push_back(Particle(start.x, start.y, start.o, _map));

	// Add some random
//	for (int i=0; i < FORK_COUNT; i++) {
//		Position pr = AddRandomParticle(start);
//		_particles.push_back(Particle(pr.x, pr.y, pr.o, _map));
//	}
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
		randDeltaX = randDeltaX * (-1.0);
	}

	// Random Y
	isNegative = rand() % 2;
	randDeltaY = rand() % deltaRand;
	if (isNegative) {
		randDeltaY = randDeltaY * (-1.0);
	}

	// Random Yaw
	isNegative = rand() % 2;
	randDeltaO = ((double)(rand() % (int)(DEGREE_2_RAD(10.0) * 100.0))) / 100.0;
	if (isNegative) {
		randDeltaO = randDeltaO * (-1.0);
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

	double bestBelif = 0.0;
	for (index=0; index < _particles.size(); index++) {
		_particles[index].Update(_lasersData, _lasersLen, dx, dy, dO);
		if (bestBelif < _particles[index].belif) {
			_bestIndex = index;
			bestBelif = _particles[index].belif;
		}
		std::cout << "Particle #" << index << ": ";
		_particles[index].position.Print();
		std::cout << " " << _particles[index].belif << std::endl;
	}

	// TODO: Add and remove particles depends on the belif
}

void LocalizationManager::AddParticle(Particle p) {
	if (_particles.size() < MAX_PARTICLES) {
		_particles.push_back(p);
	}
}

void LocalizationManager::RemoveParticle(Particle p) {
	unsigned index;

	if (_particles.size() == 1) {
		throw std::runtime_error("You can't erase the only one particle that is left :(");
	}

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

Position LocalizationManager::GetLocalizationPosition() {
	return _particles[_bestIndex].position;
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}
