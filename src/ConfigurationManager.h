/*
 * Properties.h
 *
 *  Created on: Jun 13, 2016
 *      Author: user
 */

#ifndef CNFMGR_H_
#define CNFMGR_H_

#include <iostream>
#include <map>

#include "World.h"
#include "Position.h"

class ConfigurationManager {
private:
	std::string _map;
	Position _startLocation;
	Position _goalLocation;
	signed _roboSizeX;
	signed _roboSizeY;
	double _mapResolutionCM;
	double _gridResolutionCM;
public:
	ConfigurationManager(std::string filepath);
	std::string GetMap();
	Position GetStartLocation();
	Position GetGoal();
	signed GetRobotSizeX();
	signed GetRobotSizeY();
	double GetMapResolCM();
	double GetGridResolCM();
	virtual ~ConfigurationManager();
};

#endif /* CNFMGR_H_ */
