/*
 * Grid.h
 *
 *  Created on: Apr 10, 2016
 *      Author: user
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
//using namespace std;

#include "MapUtils/Grid.h"

class AStar {
public:
	AStar(Grid grid);
	std::string getValue();
private:
	Grid _grid;
};

#endif
