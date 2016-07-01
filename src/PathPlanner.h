/*
 * Grid.h
 *
 *  Created on: Apr 10, 2016
 *      Author: user
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>

#include "World.h"
#include "MapUtils/Grid.h"
#include "Point.h"

class PathPlanner {
private:
	Grid _grid;
	Point _start;
	Point _end;
public:
	PathPlanner() {}
	PathPlanner(Grid grid, Point start, Point end);
	std::string GetPath();
};

#endif
