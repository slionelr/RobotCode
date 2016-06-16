/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#include <stdlib.h>
#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map map) {
	//_particles(); // Already initialized at declaration
	_lp = arrLaser;
	_lasersLen = lasersLen;
	_lasersData = (double*)malloc(lasersLen * sizeof(double));
	_map = map;

	for (int i=0; i < 15; i++) {
		Particle pr = Particle(rand() % map.GetWidth(),
							   rand() % map.GetHeight(),
							   rand() % (unsigned)M_PI);
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

Map LocalizationManager::GetMap() {
	return this->_map;
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}