/*
 * Map.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#include <cmath>

#include "Map.h"
#include "MapUtils/lodepng.h"

#define WHITE 0
#define BLACK 1

#define DOT_RADIUS		2
#define DIRECTION_LIMIT	10

Map::Map(std::string file, double resolution) {
	std::vector<unsigned char> image;
	unsigned height, width;
	unsigned x, y;

	_resolution = resolution;

	//Decode the image
	unsigned error = lodepng::decode(image, width, height, file);
	std::cout << "Read image file of Height: " << height << " Width: " << width << std::endl;
	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	_grid = Grid(height, width);
	// Set grid
	for (y=0; y < height; y++) {
		for (x=0; x < width; x++) {
//			std::cout
//			<< "[0: " << (int)image[y * width * 4 + x * 4 + 0] << "]" << std::endl
//			<< "[1: " << (int)image[y * width * 4 + x * 4 + 1] << "]" << std::endl
//			<< "[2: " << (int)image[y * width * 4 + x * 4 + 2] << "]" << std::endl
//			<< "[3: " << (int)image[y * width * 4 + x * 4 + 3] << "]" << std::endl << std::endl;

			if (image[y * width * 4 + x * 4 + 0] ||
				image[y * width * 4 + x * 4 + 1] ||
				image[y * width * 4 + x * 4 + 2] /*||
				image[y * width * 4 + x * 4 + 3]*/)
			{
				_grid.SetValue(y, x, WHITE);
			}
			else
			{
				_grid.SetValue(y, x, BLACK);
			}
		}
	}
}

Map::Map(Grid grid, double resolution) {
	_grid = grid;
	_resolution = resolution;
}

Map Map::Nipuha(signed rSize) {
	unsigned width = _grid.GetWidth();
	unsigned height = _grid.GetHeight();
	unsigned x,y;

	std::cout << "nipuah of: " << rSize << std::endl;

	// Clone the grid and napeah oto
	Grid nipuha = _grid.Clone();
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			int p = _grid.GetValue(y, x);
			// If its white than
			if (p == 0) // Is not zero - like white-RGB=255 in png
			{
				nipuha.SetValue(y, x, WHITE);
			}
			else
			{
				nipuha.SetValue(y, x, BLACK);

				for(signed i = -rSize; i < rSize; i++) {
					for (signed j = -rSize; j < rSize; j++) {
						if ((x+i > 0) && (x+i < width) && (y+j > 0) && (y+j < height)) {
							nipuha.SetValue(y+j, x+i, BLACK);
						}
					}
				}
			}
		}
	}

	return Map::Map(nipuha, _resolution);
}

Grid Map::GetGrid() {
	return _grid;
}

double Map::GetResolution() {
	return _resolution;
}

unsigned Map::GetHeight() {
	return _grid.GetHeight();
}

unsigned Map::GetWidth() {
	return _grid.GetWidth();
}

Map Map::Clone() {
	return Map::Map(_grid.Clone(), _resolution);
}

void Map::Print(Position p) {
	int value;
	signed height = _grid.GetHeight();
	signed width = _grid.GetWidth();

	for(signed y=0; y < height; y++)
	{
		for(signed x=0; x < width; x++) {
			value = _grid.GetValue(y,x);

			if ((p.x != 0 && p.y != 0) &&
				(p.x == x && p.y == y)) {
				std::cout << "X";
			} else {
				if(value == 0) {
					std::cout << ".";
				} else {
					std::cout << "O"; //obstacle
				}
			}
		}
		std::cout << std::endl;
	}
}

Map Map::MapGridConverter(double gridResolution) {
	unsigned height = this->GetHeight();
	unsigned width = this->GetWidth();
	unsigned matrixSize = gridResolution / _resolution;

	unsigned nh = ceil((double)height / (double)matrixSize);
	unsigned nw = ceil((double)width / (double)matrixSize);

	Grid n(nh, nw);
	for (unsigned y=0; y < height; y+=matrixSize) {
		for (unsigned x=0; x < width; x+=matrixSize) {
			int obstacle = 0;
			for (unsigned my=0; my < matrixSize; my++) {
				for (unsigned mx=0; mx < matrixSize; mx++) {
					if (y+my < height && x+mx < width) {
						int v = _grid.GetValue(y+my,x+mx);
						obstacle = obstacle | v;
					}
				}
			}
			n.SetValue(y / matrixSize, x / matrixSize, obstacle);
		}
	}

	return Map(n, gridResolution);
}

Position Map::MapToGridLocation(Position p, Map grid) {
	int convFactor = grid.GetResolution() / this->GetResolution();
	return Position(
			floor(p.x / convFactor),
			floor(p.y / convFactor)
			);
}

void Map::SaveToFile(std::string file) {
	SaveToFile(file, NULL, 0);
}

void Map::SaveToFile(std::string file, Position* parti, int partiLen) {
	// Convert map to image vector
	signed height = this->GetHeight();
	signed width = this->GetWidth();
	std::vector<unsigned char> image(height * width * 4);
	signed x,y;

	for (y=0; y < height; y++) {
		for (x=0; x < width; x++) {
			if (_grid.GetValue(y, x) == 0) {
				image[y * width * 4 + x * 4 + 0] = 255;
				image[y * width * 4 + x * 4 + 1] = 255;
				image[y * width * 4 + x * 4 + 2] = 255;
				image[y * width * 4 + x * 4 + 3] = 255;
			} else {
				image[y * width * 4 + x * 4 + 0] = 0;
				image[y * width * 4 + x * 4 + 0] = 0;
				image[y * width * 4 + x * 4 + 0] = 0;
				image[y * width * 4 + x * 4 + 3] = 255;
			}
		}
	}

	if (p.x != 0 && p.y != 0) {
		for (y=0-DOT_RADIUS; y < DOT_RADIUS; y++) {
			for (x=0-DOT_RADIUS; x < DOT_RADIUS; x++) {
				image[(p.y + y) * width * 4 + (p.x + x) * 4 + 0] = 255;
				image[(p.y + y) * width * 4 + (p.x + x) * 4 + 1] = 0;
				image[(p.y + y) * width * 4 + (p.x + x) * 4 + 2] = 0;
				image[(p.y + y) * width * 4 + (p.x + x) * 4 + 3] = 255;
			}
		}
	}

	// TODO: Sync me, Sagiv and Ariel how the Yaw is relativ to. (the XY gaph or somthing ele.
	// I say that the Yaw is like the Y direction.
	//
	//	------------>(X)
	// |
	// |    ^    == Yaw = -1 (because the direction is the oposite direction to the Y
	// |    |
	// |
	// |
	// V
	//(Y)
	double tx = 0;
	double ty = 0;
	double addX = sin(p.o);
	double addY = cos(p.o);
	int nx = 0;
	int ny = 0;

	while ((abs(nx) < DIRECTION_LIMIT) && (abs(ny) < DIRECTION_LIMIT)) {
		image[(p.y + ny) * width * 4 + (p.x + nx) * 4 + 0] = 255;
		image[(p.y + ny) * width * 4 + (p.x + nx) * 4 + 1] = 0;
		image[(p.y + ny) * width * 4 + (p.x + nx) * 4 + 2] = 0;
		image[(p.y + ny) * width * 4 + (p.x + nx) * 4 + 3] = 255;

		tx+=addX;
		ty+=addY;

		nx = tx;
		ny = ty;
	}

	//Encode the image
	unsigned error = lodepng::encode(file, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

