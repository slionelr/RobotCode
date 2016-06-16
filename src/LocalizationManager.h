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
	PlayerCc::LaserProxy* _lp;
	double* _lasersData;
	int _lasersLen;
	Map _map;
	std::vector<Particle> _particles;
public:
	LocalizationManager() {}
	LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map map);
	void Update(double dx, double dy, double dO);
	Map GetMap();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
