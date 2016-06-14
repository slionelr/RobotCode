/*
 * Map.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */

#include "Map.h"
#include "MapUtils/lodepng.h"

PixelAsInt WHITE;
PixelAsInt BLACK;

Map::Map(unsigned height, unsigned width, double resolution) {
	_grid = GridAsInt(height, width);
	_resolution = resolution;
}

Map::Map(GridAsInt grid, double resolution) {
	_grid = grid;
	_resolution = resolution;
}

Map Map::Nipuha(signed rSize) {
	unsigned width = _grid.GetWidth();
	unsigned height = _grid.GetHeight();
	unsigned x,y;

	std::cout << "nipuah of: " << rSize << std::endl;

	// Clone the grid and napeah oto
	GridAsInt nipuha = _grid.Clone();
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			PixelAsInt p = _grid.GetValue(y, x);
			// If its white than
			if (p.Value) // Is not zero - like white-RGB=255 in png
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

GridAsInt Map::GetGrid() {
	return _grid;
}

double Map::GetResolution() {
	return _resolution;
}

Map Map::Clone() {
	return Map::Map(_grid.Clone(), _resolution);
}

void Map::Print() {
	PixelAsInt p;
	unsigned height = _grid.GetHeight();
	unsigned width = _grid.GetWidth();

	for(unsigned y=0; y < height; y++)
	{
		for(unsigned x=0; x < width; x++) {
			p = _grid.GetValue(y,x);

			if(p.Value == 1) {
				std::cout << ".";
			} else if(p.Value == 0) {
				std::cout << "O"; //obstacle
			}
		}
		std::cout << std::endl;
	}
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

static Map FromFile(std::string filepath, double resolution) {
	std::vector<unsigned char> image;
	unsigned height, width;
	unsigned x, y;

	WHITE = PixelAsInt(1);
	BLACK = PixelAsInt(0);

	//Decode the image
	unsigned error = lodepng::decode(image, width, height, filepath);
	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	GridAsInt grid = GridAsInt(height, width);
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
				grid.SetValue(y, x, WHITE);
			}
			else
			{
				grid.SetValue(y, x, BLACK);
			}
		}
	}

	return Map::Map(grid, resolution);
}

static Position GetLocation(Position p, Map from, Map to) {
	return Position(); //TODO: Not implemented
}
