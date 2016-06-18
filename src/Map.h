/*
 * Map.h
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <vector>

#include "MapUtils/Grid.h"
#include "Position.h"

class Map {
private:
	Grid _grid;
	double _resolution;
	void AddDirctionsToImage(unsigned char* image, std::vector<Position> parti);
public:
	Map() {}
	Map(std::string file, double resolution);
	Map(Grid grid, double resolution);
	Map Nipuha(int size);
	Grid GetGrid();
	double GetResolution();
	Map MapGridConverter(double gridResolution);
	unsigned GetHeight();
	unsigned GetWidth();
	Map Clone();
	Position MapToGridLocation(Position p, Map grid);
	Position GridToMapLocation(Position p, Map map);
	void Print(Position p);
	void SaveToFile(std::string file);
	void SaveToFile(std::string file, std::vector<Position> parti);
	virtual ~Map();
};

#endif /* MAP_H_ */
