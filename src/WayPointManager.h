/*
 * wayPointManager.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <iostream>
#include <vector>

//#include "MapUtils/Grid.h"
//#include "PathPlanner.h"
#include "Map.h"

class WayPointManager {
private:
	Grid _grid;
	Point _start;
	Point _end;
public:
	WayPointManager() {}
	WayPointManager(Grid grid, Point start, Point end);
	std::vector<Point> GetWayPoints(std::string route);
};

#endif /* WAYPOINTMANAGER_H_ */
