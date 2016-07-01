/*
 * LocalizationManager.h
 *
 *  Created on: Jun 15, 2016
 *      Author: user
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <vector>

#include "World.h"
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

	Particle* _particles[MAX_PARTICLES];
	int _particlesCount;
	int _bestIndex;
	void AddRandomParticle(Position p);
	int AddParticle(Particle* p);
	void RemoveParticle(int index);
public:
	LocalizationManager() {}
	LocalizationManager(PlayerCc::LaserProxy* arrLaser, int lasersLen, Map map);
	void StartKnownPoint(Position start);
	void Update(double dx, double dy, double dO, Position p);
	Map GetMap();
	std::vector<Position> GetParticlesPosition();
	Position GetLocalizationPosition();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
