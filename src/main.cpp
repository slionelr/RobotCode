//============================================================================
// Name        : SLAM.cpp
// Author      : Sagiv, Ariel, Lionel
// Version     :
// Copyright   : MIT
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "ConfigurationManager.h"
#include "Robot.h"
#include "Map.h"
#include "Particle.h"

using namespace std;

int main() {
	vector<Particle> vp;

	ConfigurationManager p("/home/user/workspace/SLAM/parameters.txt");

	Robot robot("localhost", 6665);
	robot.MoveTo(0.2, 0);

	std::string f = p.GetMap();
	double d = p.GetMapResolCM();

	Map map = Map::FromFile(f, d);
	Map nipuah = map.Nipuha(5);

	// Rand particales

	while (true) {
		robot.Read();
	}

	return 0;
}
