/*
 * Particle.h
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <libplayerc++/playerc++.h>
#include "Map.h"

#define NORMAL 1

class Particle {
private:
	double belif;
	double ProbByMov(double dx, double dy, double dO);
	double ProbByLaser(double* arrLaser, int laserLen, Map map);
public:
	Position position;
//	Particle(Position p);
	Particle(double x, double y, double o);
	void Update(double* arrLaser, int laserLen, double dx, double dy, double dO, Map map);
	int operator==(const Particle &);
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
