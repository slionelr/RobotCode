//============================================================================
// Name        : SLAM.cpp
// Author      : Sagiv, Ariel, Lionel
// Version     :
// Copyright   : MIT
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "Properties.h"

#include "Robot.h"
#include "Map.h"
#include "Particle.h"

using namespace std;

int main() {
	vector<Particle> vp;

	Properties p("/home/user/workspace/SLAM/parameters.txt");

	Robot robot("localhost", 6665);
	robot.MoveTo(0.2, 0);

	Map map("/home/user/workspace/SLAM/Robotic.png");
	GridAsInt grid = map.GetGrid();
	GridAsInt nipuah = map.Nipuha(5);

	// Rand particales
	grid.PrintGrid();
	nipuah.PrintGrid();

	while (true) {
		robot.Read();
	}

	return 0;
}
