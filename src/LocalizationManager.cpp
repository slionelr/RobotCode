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

	for (int i=0; i < 15; i++) {
		Particle pr = Particle(rand() % grid.GetWidth(),
							   rand() % grid.GetHeight(),
							   (rand() % (unsigned)(M_PI * 100)) / 100);
		_particles.push_back(pr);
	}
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

void LocalizationManager::PaticlesImage() {
	std::vector<Position> v = GetParticlesPosition();
	_map.SaveToFile("particles.png", v);
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}
