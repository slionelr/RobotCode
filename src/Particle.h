/*
 * Particle.h
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <libplayerc++/playerc++.h>

#define NORMAL 1

class Particle {
private:
	double x;
	double y;
	double o;
	double belif;
public:
	Particle(double x, double y, double o);
	void Update(PlayerCc::LaserProxy* arrLaser, int laserNum, double dx, double dy, double dO, void* map);
	double ProbByMov(double dx, double dy, double dO);
	double ProbByLaser(PlayerCc::LaserProxy* arrLaser, int laserNum, void* map);
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
