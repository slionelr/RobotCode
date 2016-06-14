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
	Map(std::string file, double resolution);
	Map(GridAsInt grid, double resolution);
	Map Nipuha(int size);
	GridAsInt GetGrid();
	double GetResolution();
	Map MapGridConverter(double gridResolution);
	Position MapToGridLocation(Position p, Map grid);
	unsigned GetHeight();
	unsigned GetWidth();
	Map Clone();
	void Print();
	void SaveToFile(std::string file);
	virtual ~Map();
};

#endif /* MAP_H_ */
