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

#define NORMAL 1.8

#define LASER_RANGE_DEGREE 240
#define LASER_RESOLUTION 0.36

class Particle {
private:
//	static int _updateId; // TODO: DELETE
	int _updateId; // TODO: DELETE
	static int _id; // TODO: DELETE ID
	int _myId; // TODO: DELETE

	Map _map;
	void init(double x, double y, double o, Map map);
	double ProbByMov(double dx, double dy, double dO);
	double ProbByLaser(double* arrLaser, int lasersLen);
public:
	double belif;
	Position position;
//	Particle();
	Particle(double x, double y, double o, Map map);
	void Update(double* arrLaser, int lasersLen, double dx, double dy, double dO);
	double GetLaserAngle(int index, int lasersLen);
	int operator==(const Particle &);
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
