/*
 * GridAsInt.cpp
 *
 *  Created on: May 24, 2016
 *      Author: user
 */

#include "GridAsInt.h"
GridAsInt::GridAsInt(){};
GridAsInt::GridAsInt(unsigned height, unsigned width) {
	_height = height;
	_width = width;
	_arr = (PixelAsInt**)malloc(sizeof(PixelAsInt*) * height);
	for (unsigned y=0; y < height; y++) {
		_arr[y] = (PixelAsInt*)malloc(sizeof(PixelAsInt) * width);
		for (unsigned x=0; x < width; x++) {
			_arr[y][x] = PixelAsInt();
		}
	}
}

unsigned GridAsInt::GetHeight() {
	return _height;
}

unsigned GridAsInt::GetWidth() {
	return _width;
}

PixelAsInt GridAsInt::GetValue(unsigned row, unsigned col) {
	return _arr[row][col];
}

void GridAsInt::SetValue(unsigned row, unsigned col, PixelAsInt value) {
	_arr[row][col] = value;
}

GridAsInt GridAsInt::Clone() {
	GridAsInt temp(_height, _width);
	for (unsigned y=0; y < _height; y++) {
		for (unsigned x=0; x < _width; x++) {
			temp.SetValue(y,x, _arr[y][x]);
		}
	}

	return temp;
}

void GridAsInt::PrintGrid() {
	PixelAsInt p;
	for(unsigned y=0; y < _height; y++)
	{
		for(unsigned x=0; x < _width; x++) {
			p = _arr[y][x];

			if(p.Value == 1) {
				std::cout << ".";
			} else if(p.Value == 0) {
				std::cout << "O"; //obstacle
			}
		}
		std::cout << std::endl;
	}
}

void GridAsInt::PrintXY(unsigned r, unsigned c) {
	PixelAsInt p;
	for(unsigned y=0; y < _height; y++)
	{
		for(unsigned x=0; x < _width; x++) {
			p = _arr[y][x];

			if (r==y && c==x) {
				std::cout << "X";
			} else {
				if(p.Value == 1) {
					std::cout << ".";
				} else if(p.Value == 0) {
					std::cout << "O"; //obstacle
				}
			}
		}
		std::cout << std::endl;
	}
}
