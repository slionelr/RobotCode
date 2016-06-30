/*
 * Particle.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: user
 */
#include <cmath>

#include <sstream> // TODO: DELETE

#include "Particle.h"

//Particle::Particle() {
//	init(0,0,0,Map());
//}

int Particle::_id = 0; // TODO: Delete
int Particle::_updateId = 0; // TODO: Delete

Particle::Particle(double x, double y, double o, Map map) {
	init(x,y,o,map);
}

void Particle::init(double x, double y, double o, Map map) {
//	this->_updateId = 0;
	this->_myId = _id;
	++_id;

	this->position.x = x;
	this->position.y = y;
	this->position.o = o;
	this->_map = map;
	// TODO: Change the stating belif value (maybe need to get it from the constructor)
	this->belif = 1.0; // !!!!!
}

void Particle::Update(double* arrLaser, int lasersLen, double dx, double dy, double dO, double* avDisMis, double* avAngleMis) {
	double mistake;

	// Update the particle position using the delta values
	this->position.x = this->position.x + dx;
	this->position.y = this->position.y + dy;
	this->position.o = this->position.o + dO;

	// Get the predictable belif
	double preBelif = belif * ProbByMov(dx, dy, dO);
	// Get the NEW belif
	double probLasers = ProbByLaser(arrLaser, lasersLen, avDisMis, avAngleMis);
	belif = NORMAL * preBelif * probLasers;
}

double Particle::ProbByMov(double dx, double dy, double dO) {
	double probO = 1.0;
	double deltaYaw = abs(dO);

	if (deltaYaw < (M_PI / 4)) {
		probO = 0.9;
	} else if (deltaYaw < (M_PI / 2)) {
		probO = 0.8;
	} else if (deltaYaw < (3 * M_PI / 4)) {
		probO = 0.7;
	} else {
		probO = 0.6;
	}

	double d = pow(dx, 2) + pow(dy, 2);
	d = sqrt(d);

	if (d < 1.0) {
		probO = probO * 0.95;
	} else {
		probO = probO * 0.9;
	}

//	return probO;
	return 1.0;
}

double Particle::ProbByLaser(double* arrLaser, int lasersLen, double* avDisMis, double* avAngleMis) {
	const double MAX_LASER_DISTANCE = 4.0;
	double misCounter = 0;
	double mr_Counter = 0;

	double disCheckCounter = 0.0;
	double adm = 0.0;
	double aam = 0.0;


	// TODO: DELETE TEMP IMAGE SAVE
	std::vector<Position> obs;

	for (int i=0; i < lasersLen; i++) {
		double obsDistance = arrLaser[i];

		// If there is an object in-front of this laser than score it
		if (obsDistance < MAX_LASER_DISTANCE && obsDistance > 0.0) {
			double lsrAngle = GetLaserAngle(i, lasersLen);
			double mapAngle = position.o + lsrAngle;
//			std::cout << "[Angle: " << mapAngle << "][ObstDis: " << obsDistance << "]" << std::endl;

			double x = obsDistance * cos(mapAngle);
			double y = obsDistance * sin(mapAngle);

			x = METER_TO_CM(x);
			y = AXIS_REDIRECT(METER_TO_CM(y));

			x = x + position.x;
			y = y + position.y;
			Position np = _map.ConvertLocation(Position(x,y,0));

			if ((np.x < 0.0) || (np.x >= _map.GetWidth()) ||
				(np.y < 0.0) || (np.y >= _map.GetHeight())) {
				misCounter++;
			} else {
				obs.push_back(np);

				int value = _map.GetValue(np.y, np.x);
				if (value) {
					mr_Counter++;
				} else {
					for (double ni=-1.0; ni < 1.0; ni=ni+0.1) {
						double rangeOobsDistance = obsDistance + ni;
						if (rangeOobsDistance > 0.0) {
							double nx = rangeOobsDistance * cos(mapAngle);
							double ny = rangeOobsDistance * sin(mapAngle);
							nx = METER_TO_CM(nx);
							ny = AXIS_REDIRECT(METER_TO_CM(ny));
							nx = nx + position.x;
							ny = ny + position.y;
							Position tnp = _map.ConvertLocation(Position(nx,ny,0));

							if ((tnp.x < 0.0) || (tnp.x >= _map.GetWidth()) ||
								(tnp.y < 0.0) || (tnp.y >= _map.GetHeight())) {
								continue;
							} else {
								value = _map.GetValue(tnp.y, tnp.x);
								if (value) {
									adm = adm + ni;
									aam = aam + i;
									disCheckCounter = disCheckCounter + 1.0;
									std::cout << "There is a obstacle in " << ni << " mistake." << std::endl;
									break;
								}
							}
						}
					}
					misCounter++;
				}
			}
		}
	}

//	for (int i=0; i<obs.size(); i++) {
//		std::cout << "Obs[" << i << "]";
//		obs[i].Print();
//		std::cout << std::endl;
//	}

	std::stringstream ss;
	ss << "update_" << Particle::_updateId << "__obsticles.parti." << _myId << ".png";
	obs.push_back(_map.ConvertLocation(position));
	_map.SaveToFile(ss.str(), obs);

	adm = adm / disCheckCounter;
	aam = aam / disCheckCounter;
	aam = DEGREE_2_RAD(aam);
	aam = aam - M_2PI_;

	*avDisMis = adm;
	*avAngleMis = aam;

	if ((misCounter + mr_Counter) == 0) {
		return 1.0;
	} else {
		return mr_Counter / (misCounter + mr_Counter);
	}
}

double Particle::GetLaserAngle(int index, int lasersLen) {
	// range-of-lasers(240) / resolution(0.36) => 666 samples <=> _laserLen
	double degree = (LASER_RESOLUTION * index) - (((double)lasersLen * LASER_RESOLUTION) / 2.0);
	return DEGREE_2_RAD(degree);
}

int Particle::operator==(const Particle &r) {
	return ((position.x == r.position.x) &&
			(position.y == r.position.y));
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}
