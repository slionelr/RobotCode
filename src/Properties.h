/*
 * Properties.h
 *
 *  Created on: Jun 13, 2016
 *      Author: user
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <iostream>
#include <map>

#include "Position.h"

class Properties {
private:
	std::string _map;
	Position _startLocation;
	Position _goalLocation;
	signed _roboSizeX;
	signed _roboSizeY;
	double _mapResolutionCM;
	double _gridResolutionCM;
public:
	Properties(std::string filepath);
	std::string GetMap();
	Position GetStartLocation();
	Position GetGoal();
	signed GetRobotSizeX();
	signed GetRobotSizeY();
	double GetMapResolCM();
	double GetGridResolCM();
	virtual ~Properties();
};

#endif /* PROPERTIES_H_ */
