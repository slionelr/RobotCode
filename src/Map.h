/*
 * Map.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "MapUtils/GridAsInt.h"
#include "Position.h"

class Map {
private:
	GridAsInt _grid;
	double _resolution;
public:
	Map(unsigned height, unsigned width, double resolution);
	Map(GridAsInt grid, double resolution);
	Map Nipuha(int size);
	GridAsInt GetGrid();
	double GetResolution();
	Map Clone();
	void Print();
	virtual ~Map();
	static Map FromFile(std::string filepath, double resolution);
	static Position GetLocation(Position p, Map from, Map to);
};

#endif /* MAP_H_ */
