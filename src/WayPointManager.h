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
#include "aStar.h"


class WayPointManager {
private:
	Grid _grid;
public:
	WayPointManager(Grid grid);
	void getWayPoint();
};

#endif
