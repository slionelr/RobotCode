/*
 * Map.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#include <iostream>

#ifndef MAP_H_
#define MAP_H_

#include "MapUtils/GridAsInt.h"

#define ROBO_SIZE_H 30
#define ROBO_SIZE_W 30
#define REZOLUTION	2.5

class Map {
private:
	GridAsInt _grid;
public:
	Map(std::string mapPath);
	GridAsInt Nipuha(int size);
	GridAsInt GetGrid();
	virtual ~Map();
};

#endif /* MAP_H_ */
