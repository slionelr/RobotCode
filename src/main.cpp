//============================================================================
// Name        : SLAM.cpp
// Author      : Sagiv, Ariel, Lionel
// Version     :
// Copyright   : MIT
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>

#include "ConfigurationManager.h"
#include "Robot.h"
#include "Map.h"
#include "Particle.h"

int main() {
	std::vector<Particle> vp;

	ConfigurationManager cnf("parameters.txt");

//	Robot robot("localhost", 6665);
//	robot.MoveTo(0.2, 0);

	Map map = Map(cnf.GetMap(), cnf.GetMapResolCM());
	Map grid = map.MapGridConverter(cnf.GetGridResolCM());

	grid.SaveToFile("zprint.png");
	grid.Print();

//	Map nipuah = map.Nipuha(5);

	// Rand particales

//	while (true) {
//		robot.Read();
//	}

	return 0;
}
