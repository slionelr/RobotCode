/*
 * GridAsInt.cpp
 *
 *  Created on: May 24, 2016
 *      Author: user
 */

#include "Grid.h"

Grid::Grid() {};

Grid::Grid(unsigned height, unsigned width) {
	_height = height;
	_width = width;
	_arr = (int**)malloc(sizeof(int*) * height);
	for (unsigned y=0; y < height; y++) {
		_arr[y] = (int*)malloc(sizeof(int) * width);
		for (unsigned x=0; x < width; x++) {
			_arr[y][x] = 0;
		}
	}
}

unsigned Grid::GetHeight() {
	return _height;
}

unsigned Grid::GetWidth() {
	return _width;
}

int Grid::GetValue(unsigned row, unsigned col) {
	return _arr[row][col];
}

void Grid::SetValue(unsigned row, unsigned col, int value) {
	_arr[row][col] = value;
}

Grid Grid::Clone() {
	Grid temp(_height, _width);
	for (unsigned y=0; y < _height; y++) {
		for (unsigned x=0; x < _width; x++) {
			temp.SetValue(y,x, _arr[y][x]);
		}
	}

	return temp;
}

void Grid::PrintGrid() {
	int p;
	for(unsigned y=0; y < _height; y++)
	{
		for(unsigned x=0; x < _width; x++) {
			p = _arr[y][x];

			if(p == 1) {
				std::cout << ".";
			} else if(p == 0) {
				std::cout << "O"; //obstacle
			}
		}
		std::cout << std::endl;
	}
}

void Grid::PrintXY(unsigned r, unsigned c) {
	int p;
	for(unsigned y=0; y < _height; y++)
	{
		for(unsigned x=0; x < _width; x++) {
			p = _arr[y][x];

			if (r==y && c==x) {
				std::cout << "X";
			} else {
				if(p == 1) {
					std::cout << ".";
				} else if(p == 0) {
					std::cout << "O"; //obstacle
				}
			}
		}
		std::cout << std::endl;
	}
}
