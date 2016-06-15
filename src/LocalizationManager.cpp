/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen) {
	//_particles(); // Already initialized at declaration
	_lp = arrLaser;
	_lasersLen = lasersLen;
	_lasersData = (double*)malloc(lasersLen * sizeof(double));
}

void LocalizationManager::Update() {
	for (int index=0; index < _lasersLen; index++) {
		_lasersData[index] = _lp->GetRange(index);
	}
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}
