#ifndef GRID_AS_INT_H_
#define GRID_AS_INT_H_

#include <iostream>

class Grid {
public:
	Grid();
	Grid(unsigned height, unsigned width);
	unsigned GetHeight();
	unsigned GetWidth();
	int GetValue(unsigned row, unsigned col);
	void SetValue(unsigned row, unsigned col, int value);
	Grid Clone();
	void PrintGrid();
	void PrintXY(unsigned r, unsigned c);
private:
	unsigned _height;
	unsigned _width;
	int** _arr;
};

#endif
