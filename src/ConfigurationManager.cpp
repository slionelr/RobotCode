/*
 * Properties.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: user
 */

#include <fstream>
#include <sstream>
#include <exception>
#include "ConfigurationManager.h"

const std::string MAP				= "map:";
const std::string START_LOCATION	= "startlocation:";
const std::string GOAL				= "goal:";
const std::string ROBOT_SIZE		= "robotsize:";
const std::string MAP_RESOL_CM		= "mapresolutioncm:";
const std::string GRID_RESOL_CM		= "gridresolutioncm:";

ConfigurationManager::ConfigurationManager(std::string filepath) {
	try {
		std::ifstream file(filepath.c_str());
		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string pname, pvalue;
			if (!(iss >> pname)) {
				// EOF
			} else {
				std::string key;
				std::transform(pname.begin(), pname.end(), std::back_inserter(key), ::tolower);

				if (key.compare(MAP) == 0) {
					iss >> _map;
				} else if (key.compare(START_LOCATION) == 0) {
					signed x, y, o;
					iss >> x >> y >> o;
					_startLocation = Position(x,y,o);
				} else if (key.compare(GOAL) == 0) {
					signed x, y;
					iss >> x >> y;
					_goalLocation = Position(x,y);
				} else if (key.compare(ROBOT_SIZE) == 0) {
					iss >> _roboSizeX >> _roboSizeY;
				} else if(key.compare(MAP_RESOL_CM) == 0) {
					iss >> _mapResolutionCM;
				} else if(key.compare(GRID_RESOL_CM) == 0) {
					iss >> _gridResolutionCM;
				} else {
					std::cout << "Unknown read property name: " << pname << std::endl;
				}
			}
		}
	}
	catch (std::exception& e) {
		std::cout << "EXCEPTION" << std::endl;
	}
}

std::string ConfigurationManager::GetMap() { return _map; }
Position ConfigurationManager::GetStartLocation() { return _startLocation; }
Position ConfigurationManager::GetGoal() { return _goalLocation; }
signed ConfigurationManager::GetRobotSizeX() { return _roboSizeX; }
signed ConfigurationManager::GetRobotSizeY() { return _roboSizeY; }
double ConfigurationManager::GetMapResolCM() { return _mapResolutionCM; }
double ConfigurationManager::GetGridResolCM() { return _gridResolutionCM; }

ConfigurationManager::~ConfigurationManager() {
	// TODO Auto-generated destructor stub
}
