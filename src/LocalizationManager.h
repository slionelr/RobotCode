/*
 * LocalizationManager.h
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#include <vector>
#include "Particle.h"

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

class LocalizationManager {
private:
	std::vector<Particle> _particles;
	PlayerCc::LaserProxy* _lp;
	double* _lasersData;
	int _lasersLen;
public:
	LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen);
	void Update();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
