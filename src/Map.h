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

#include "World.h"
#include "MapUtils/Grid.h"
#include "Position.h"

#include "MapUtils/RGB.h"

#define METER_TO_CM(m) (m * 10.0)
#define CM_TO_METER(cm) (cm / 10.0)
#define AXIS_REDIRECT(v) (v * -1.0)

#define M_2PI_ (2 * M_PI)

class Map {
private:
	Grid _grid;
	double _convResolution;
	void AddDirctionsToImage(unsigned char* image, std::vector<Position> parti);
	void Color(unsigned char* image, Position p, RGB color);
public:
	Map() {}
	Map(std::string file, double convResolution);
	Map(Grid grid, double resolution);
	Map Nipuha(int size);
	int GetValue(int y, int x);
	Grid GetGrid();
	double GetResolution();
	Map MapGridConverter(double convResolution);
	unsigned GetHeight();
	unsigned GetWidth();
	Map Clone();
	Position ConvertLocation(Position p);
	void Print(Position p);
	void SaveToFile(std::string file);
	void SaveToFile(std::string file, std::vector<Position> parti);
	virtual ~Map();
};

#endif /* MAP_H_ */
