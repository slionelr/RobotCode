/*
 * Grid.cpp
 *
 *  Created on: Apr 10, 2016
 *      Author: user
 */

#include "Grid.h"

Grid::Grid(unsigned height, unsigned width) {
	_height = height;
	_width = width;
	_arr = (Pixel**)malloc(sizeof(Pixel*) * height);
	for (unsigned y=0; y < height; y++) {
		_arr[y] = (Pixel*)malloc(sizeof(Pixel) * width);
		for (unsigned x=0; x < width; x++) {
			_arr[y][x] = Pixel();
		}
	}
}

unsigned Grid::GetHeight() {
	return _height;
}

unsigned Grid::GetWidth() {
	return _width;
}

Pixel Grid::GetValue(unsigned row, unsigned col) {
	return _arr[row][col];
}

void Grid::SetValue(unsigned row, unsigned col, Pixel value) {
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
