/*
 * LocalizationManager.h
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <vector>
#include "Point.h"
#include "Particle.h"

#define MAX_PARTICLES 50

class LocalizationManager {
private:
	PlayerCc::LaserProxy* _lp;
	double* _lasersData;
	int _lasersLen;
	Map _map;
	std::vector<Particle> _particles;
public:
	LocalizationManager() {}
	LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map grid);
	void Update(double dx, double dy, double dO);
	void AddParticle(Particle p);
	void RemoveParticle(Particle p);
	Map GetMap();
	std::vector<Position> GetParticlesPosition();
	void PaticlesImage();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
