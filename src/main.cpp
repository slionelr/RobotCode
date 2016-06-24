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
	ConfigurationManager cnf("parameters.txt");

	// Set the maps
	Map map = Map(cnf.GetMap(), cnf.GetMapResolCM() / cnf.GetGridResolCM());
	Map grid = map.MapGridConverter(cnf.GetGridResolCM() / cnf.GetMapResolCM());
	Map nipuha = grid.Nipuha(3);

	// Get the grid locations
	Position startGridLoc = nipuha.ConvertLocation(cnf.GetStartLocation());
	Position goalGridLoc = nipuha.ConvertLocation(cnf.GetGoal());

	// Start the robot
#ifdef REAL
	Robot robot("10.10.245.63", 6665, nipuha);
#else
	Robot robot("localhost", 6665, nipuha);
#endif
	robot.SetOdometry(startGridLoc);
	// Print start particles + Robot position
//	robot.SaveParticles();
//	robot.SaveParticles(map);

//	std::vector<Particle> vp;

	// Plan the path and get the waypoints
	PathPlanner plan(nipuha.GetGrid(), startGridLoc.GetPoint(), goalGridLoc.GetPoint());
	WaypointsManager mngWaypoints(nipuha.GetGrid(), startGridLoc.GetPoint());

	std::string path = plan.GetPath();
	// TODO: Handle situation when there is no path
	std::vector<Point> wp = mngWaypoints.GetWayPoints(path);

	for (int i=1; i < wp.size(); i++) {
		std::cout << "Moving to waypoint: #" << i << " ";
		wp[i].Print();
		robot.MoveTo(wp[i]);
	}

	return 0;
}
