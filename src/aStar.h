/*
 * Grid.h
 *
 *  Created on: Apr 10, 2016
 *      Author: user
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>

#include "MapUtils/Grid.h"
#include "Point.h"

class AStar {
public:
	AStar(Grid grid, Point start, Point end);
	std::string getValue();
private:
	Grid _grid;
	Point _start;
	Point _end;
};

#endif
