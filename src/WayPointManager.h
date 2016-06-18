/*
 * wayPointManager.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_


//#endif /* WAYPOINTMANAGER_H_ */
#include <iostream>

#include "MapUtils/Grid.h"
//#include "Point.h"
#include "aStar.h"


class WayPointManager {
private:
	Grid _grid;
	Point _start;
	Point _end;
public:
	WayPointManager(Grid grid, Point start, Point end);
	void GetWayPoint();
};

#endif
