#ifndef GRID_AS_INT_H_
#define GRID_AS_INT_H_

#include <iostream>

#include "PixelAsInt.h"

class GridAsInt {
public:
	GridAsInt();
	GridAsInt(unsigned height, unsigned width);
	unsigned GetHeight();
	unsigned GetWidth();
	PixelAsInt GetValue(unsigned row, unsigned col);
	void SetValue(unsigned row, unsigned col, PixelAsInt value);
	GridAsInt Clone();
	void PrintGrid();
	void PrintXY(unsigned r, unsigned c);
private:
	unsigned _height;
	unsigned _width;
	PixelAsInt** _arr;
};

#endif
