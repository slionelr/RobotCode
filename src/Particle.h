/*
 * Particle.h
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <libplayerc++/playerc++.h>
#include "World.h"
#include "Map.h"

#define NORMAL 1.7

#define LASER_RANGE_DEGREE 240
#define LASER_RESOLUTION 0.36

class Particle {
private:
	static int _id; // TODO: DELETE ID

	Map _map;
	void init(double x, double y, double o, Map map);
	double ProbByMov(double dx, double dy, double dO);
	double ProbByLaser(double* arrLaser, int lasersLen, Position* estimated);
public:
	int _myId; // TODO: DELETE
	static int _updateId; // TODO: DELETE
	double belif;
	Position position;
	Particle(double x, double y, double o, Map map);
	Position Update(double* arrLaser, int lasersLen, double dx, double dy, double dO);
	double GetLaserAngle(int index, int lasersLen);
	int operator==(const Particle &);
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
