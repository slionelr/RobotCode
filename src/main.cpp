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
#include <libplayerc++/playerc++.h>

#include "ConfigurationManager.h"
#include "Robot.h"
#include "Map.h"
#include "Particle.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"

int main() {
//	std::vector<Particle> vp;

	ConfigurationManager cnf("parameters.txt");

	Map map = Map(cnf.GetMap(), cnf.GetMapResolCM());
	Map grid = map.MapGridConverter(cnf.GetGridResolCM());
	Map nipuha = grid.Nipuha(1);

	Robot robot("localhost", 6665, nipuha);
	robot.SetOdometry(cnf.GetStartLocation());
//	robot.SetSpeed(0.1, 0.1);
//	robot.SaveParticles();

	Position startGridLoc = map.MapToGridLocation(cnf.GetStartLocation(), nipuha);
	Position goalGridLoc = map.MapToGridLocation(cnf.GetGoal(), nipuha);
	PathPlanner plan(nipuha.GetGrid(), startGridLoc.GetPoint(), goalGridLoc.GetPoint());
	WaypointsManager a(nipuha.GetGrid(), startGridLoc.GetPoint());
	std::vector<Point> wp = a.GetWayPoints(plan.GetPath());

//	std::vector<Position> parti;
//	parti.push_back(Position(20, 60, -0.2));
//	parti.push_back(Position(50, 60, 0.4));
//	parti.push_back(Position(70, 20, 1.1));

//	Position p = Position(20, 60, -0.2);
//	p.Print();
//	map.SaveToFile("zprint.png", &parti[0], parti.size());
//	map.Print(p);

	// Rand particales
//	int i = 1;
//	while (true) {
//		robot.Read();
//		Position p = robot.GetPosition();
//		p.Print();
//		map.SaveToFile("zprint.png", p);
//
//		std::cout << "Loop " << i << std::endl;
//		i++;
//	}

	return 0;
}
