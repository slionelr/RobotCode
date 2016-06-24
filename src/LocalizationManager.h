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

#define FORK_COUNT 3
#define MAX_PARTICLES 30

class LocalizationManager {
private:
	PlayerCc::LaserProxy* _lp;
	double* _lasersData;
	int _lasersLen;
	Map _map;
	std::vector<Particle> _particles;
	Position AddRandomParticle(Position p);
public:
	LocalizationManager() {}
	LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map grid);
	void StartKnownPoint(Position start);
	void Update(double dx, double dy, double dO);
	void AddParticle(Particle p);
	void RemoveParticle(Particle p);
	Map GetMap();
	std::vector<Position> GetParticlesPosition();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
