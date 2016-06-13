/*
 * Grid.h
 *
 *  Created on: Apr 10, 2016
 *      Author: user
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>

#include "Pixel.h"

class Grid {
public:
	Grid(unsigned height, unsigned width);
	unsigned GetHeight();
	unsigned GetWidth();
	Pixel GetValue(unsigned row, unsigned col);
	void SetValue(unsigned row, unsigned col, Pixel value);
	Grid Clone();
private:
	unsigned _height;
	unsigned _width;
	Pixel** _arr;
};

#endif /* GRID_H_ */
