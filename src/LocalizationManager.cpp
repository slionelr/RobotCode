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
//	_particlesCount = 0;
//	for (int i=0; i < MAX_PARTICLES; i++) {
//		_particles[i] = NULL;
//	}
	_particles.reserve(MAX_PARTICLES);

	_lp = arrLaser;
	_lasersLen = lasersLen;
	_lasersData = (double*)malloc(lasersLen * sizeof(double));
	_map = map;
}

void LocalizationManager::StartKnownPoint(Position start) {
	// Add robot start position
	AddParticle(new Particle(start.x, start.y, start.o, _map));
	_bestIndex = 0;

	// Add some random TODO: Its not good right now
//	for (int i=0; i < FORK_COUNT; i++) {
//		AddRandomParticle(start);
//	}
}

void LocalizationManager::AddRandomParticle(Position p) {
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

//	Position ret = Position(p.x + randDeltaX,
//							p.y + randDeltaY,
//							p.o + randDeltaO);
//	return ret;

	AddParticle(new Particle(p.x + randDeltaX, p.y + randDeltaY, p.o + randDeltaO, _map));
}

void LocalizationManager::Update(double dx, double dy, double dO, Position p) {
	int index;
	bool partiToDelete[MAX_PARTICLES];

	for (index=0; index < MAX_PARTICLES; index++) {
		partiToDelete[index] = false;
	}

	for (index=0; index < _lasersLen; index++) {
		_lasersData[index] = _lp->GetRange(index);
	}

	double avgX = p.x;
	double avgY = p.y;

	double bestBelif = 0.0;
	for (index=0; index < _particles.size(); index++) {
		if (_particles[index] == NULL) {
			continue;
		} else if (_particles[index]->first) {
			_particles[index]->first = false;
			continue;
		}

		Position mistake = _particles[index]->Update(_lasersData, _lasersLen, dx, dy, dO);

		std::cout << "Particle #" << _particles[index]->_myId << ": ";
		_particles[index]->position.Print();
		std::cout << " " << _particles[index]->belif << std::endl;

		// Try to put new particles with correction to the mistake that was given above
		double belif = _particles[index]->belif;

		avgX = avgX + mistake.x * belif;
		avgY = avgY + mistake.y * belif;

		if ((belif > 0.6) || (Particle::_updateId < 1))
		{
//			double ryaw = rand() % 30 - 15.0;
//			ryaw = DEGREE_2_RAD(ryaw);
//			ryaw = ryaw / 2.0;

			double ryaw = 1.0;
//			ryaw = DEGREE_2_RAD(ryaw);
			ryaw = 0.0087;

//			int move = (3 - belif);

			std::cout << "From particle #" << _particles[index]->_myId << " we create:" << std::endl;

			Particle* up = new Particle(
					_particles[index]->position.x,
					_particles[index]->position.y - mistake.y,
					mistake.o + ryaw, _map);
			std::cout << "New particle at: ";
			up->position.Print();
			std::cout << std::endl;

			Particle* right = new Particle(
					_particles[index]->position.x + mistake.x,
					_particles[index]->position.y,
					mistake.o + ryaw, _map);
			std::cout << "New particle at: ";
			right->position.Print();
			std::cout << std::endl;

			Particle* down = new Particle(
					_particles[index]->position.x,
					_particles[index]->position.y + mistake.y,
					mistake.o - ryaw, _map);
			std::cout << "New particle at: ";
			down->position.Print();
			std::cout << std::endl;

			Particle* left = new Particle(
					_particles[index]->position.x - mistake.x,
					_particles[index]->position.y,
					mistake.o - ryaw, _map);
			std::cout << "New particle at: ";
			left->position.Print();
			std::cout << std::endl;

			AddParticle(up);
			AddParticle(right);
			AddParticle(down);
			AddParticle(left);

			partiToDelete[index] = false;
		} else {
			partiToDelete[index] = true;
		}

		// Check best particle
		if (bestBelif < _particles[index]->belif) {
			_bestIndex = index;
			bestBelif = _particles[index]->belif;
		}
	}

	// Print the best particle
	std::cout << "Best Particle #" << _particles[_bestIndex]->_myId;
	_particles[_bestIndex]->position.Print();
	std::cout << std::endl;

	// Remove particles from end to start
	index--;
	for (; index >=0; index--) {
		if (partiToDelete[index] && index !=_bestIndex) {
			RemoveParticle(index);
		}
	}

	Particle::_updateId++;
}

void LocalizationManager::AddParticle(Particle* p) {
	if (MAX_PARTICLES <= _particles.size()) {
		// Reached the limit number of particles
		return;
	}

	_particles.push_back(p);
}

void LocalizationManager::RemoveParticle(int index) {
	// IF its the last particle keep it alive
	if (_particles.size() == 1) {
		return;
	}
	_particles[index] = NULL;
}

Map LocalizationManager::GetMap() {
	return this->_map;
}

std::vector<Position> LocalizationManager::GetParticlesPosition() {
	std::vector<Position> v;
	for (int i=0; i < _particles.size(); i++) {
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
