/*
 * Map.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "MapUtils/Grid.h"
#include "Position.h"

class Map {
private:
	Grid _grid;
	double _resolution;
public:
	Map(std::string file, double resolution);
	Map(Grid grid, double resolution);
	Map Nipuha(int size);
	Grid GetGrid();
	double GetResolution();
	Map MapGridConverter(double gridResolution);
	Position MapToGridLocation(Position p, Map grid);
	unsigned GetHeight();
	unsigned GetWidth();
	Map Clone();
	void Print(Position p);
	void SaveToFile(std::string file);
	void SaveToFile(std::string file, Position p);
	virtual ~Map();
};

#endif /* MAP_H_ */
