/*
 * wayPointManager.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <iostream>
#include <vector>

#include "World.h"
//#include "MapUtils/Grid.h"
//#include "PathPlanner.h"
#include "Map.h"

class WaypointsManager {
private:
	Grid _grid;
	Point _start;
public:
	WaypointsManager() {}
	WaypointsManager(Grid grid, Point start);
	std::vector<Point> GetWayPoints(std::string route);
};

#endif /* WAYPOINTSMANAGER_H_ */
