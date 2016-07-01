/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#include <stdlib.h>
#include <stdexcept>
#include <cmath>
#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map map) {
	_particlesLength = 0;
	for (int i=0; i < MAX_PARTICLES; i++) {
		_particles[i] = NULL;
	}

	_lp = arrLaser;
	_lasersLen = lasersLen;
	_lasersData = (double*)malloc(lasersLen * sizeof(double));
	_map = map;
}

void LocalizationManager::StartKnownPoint(Position start) {
	// Add robot start position
	AddParticle(new Particle(start.x, start.y, start.o, _map));

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
	// The particles vector size before we add more - this probebly solves a problem
	int partiVecSize = _particlesLength;
	bool* partiDeleteParti = (bool*)malloc(partiVecSize * sizeof(bool));
	for (index=0; index < partiVecSize; index++) {
		if (_particles[index] == NULL) {
			continue;
		}

		Position mistake = _particles[index]->Update(_lasersData, _lasersLen, dx, dy, dO);

		// Try to put new particles with correction to the mistake that was given above
//		if (_particles[index]->belif > 0.5)
//		{
			// TODO: TEST LOOP - delete after finish testing
			for (int k=2; k <= 2; k++){
//			double ryaw = rand() % 30 - 15.0;
//			ryaw = DEGREE_2_RAD(ryaw);
//			ryaw = ryaw / 2.0;

			double ryaw = 2.0;
			ryaw = k * ryaw;
			ryaw = DEGREE_2_RAD(ryaw);

			Particle* a = new Particle(mistake.x, mistake.y, mistake.o + ryaw, _map);
			std::cout << "New particle at: ";
			a->position.Print();
			std::cout << std::endl;

			Particle* b = new Particle(mistake.x, mistake.y, mistake.o - ryaw, _map);
			std::cout << "New particle at: ";
			b->position.Print();
			std::cout << std::endl;

			AddParticle(a);
			AddParticle(b);
			}

			partiDeleteParti[index] = false;
//		} else {
//			partiDeleteParti[index] = true;
//		}

		// Check best particle
		if (bestBelif < _particles[index]->belif) {
			_bestIndex = index;
			bestBelif = _particles[index]->belif;
		}
		std::cout << "Particle #" << index << ": ";
		_particles[index]->position.Print();
		std::cout << " " << _particles[index]->belif << std::endl;
	}

	// Remove particles from end to start
	for (; index >=0; index--) {
		if (partiDeleteParti[index]) {
			RemoveParticle(index);
		}
	}

	Particle::_updateId++;
}

void LocalizationManager::AddParticle(Particle* p) {
	if (_particlesLength < MAX_PARTICLES) {
		for (int i=0; i < _particlesLength + 1; i++) {
			if (_particles[i] == NULL) {
				_particles[_particlesLength] = p;
			}
		}
		_particlesLength++;
	}
}

void LocalizationManager::RemoveParticle(int index) {
	// IF its the last particle keep it alive
	if (_particlesLength == 0) {
		return;
	}
	_particles[index] = NULL;
	_particlesLength--;
}

Map LocalizationManager::GetMap() {
	return this->_map;
}

std::vector<Position> LocalizationManager::GetParticlesPosition() {
	std::vector<Position> v;
	for (int i=0; i < _particlesLength; i++) {
		v.push_back(_particles[i]->position);
	}
	return v;
}

Position LocalizationManager::GetLocalizationPosition() {
	return _particles[_bestIndex]->position;
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}
