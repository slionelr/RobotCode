/*
 * Properties.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: user
 */

#include <fstream>
#include <sstream>
#include <exception>
#include "Properties.h"

Properties::Properties(std::string filepath) {
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

				if (key.compare("map:") == 0) {
					iss >> _map;
				} else if (key.compare("startlocation:") == 0) {
					signed x, y, o;
					iss >> x >> y >> o;
					_startLocation = Position(x,y,o);
				} else if (key.compare("goal:") == 0) {
					signed x, y;
					iss >> x >> y;
					_goalLocation = Position(x,y);
				} else if (key.compare("robotsize:") == 0) {
					iss >> _roboSizeX >> _roboSizeY;
				} else if(key.compare("mapresolutioncm:") == 0) {
					iss >> _mapResolutionCM;
				} else if(key.compare("gridresolutioncm:") == 0) {
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

std::string Properties::GetMap() { return _map; }
Position Properties::GetStartLocation() { return _startLocation; }
Position Properties::GetGoal() { return _goalLocation; }
signed Properties::GetRobotSizeX() { return _roboSizeX; }
signed Properties::GetRobotSizeY() { return _roboSizeY; }
double Properties::GetMapResolCM() { return _mapResolutionCM; }
double Properties::GetGridResolCM() { return _gridResolutionCM; }

Properties::~Properties() {
	// TODO Auto-generated destructor stub
}
