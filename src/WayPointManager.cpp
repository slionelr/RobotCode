/*
* wayPointManager.cpp
*
*  Created on: Jun 10, 2016
*      Author: user
*/
#include <iostream>
#include <vector>
#include <math.h>

#include "WayPointManager.h"

using namespace std;
WayPointManager::WayPointManager(Grid grid, Point start, Point end) {
	_grid = grid;
	_start = start;
	_end = end;
}

void WayPointManager::GetWayPoint() {
	AStar a(_grid, _start, _end);
	string route = a.getValue();
	int previusDirection = -1;
	int countCurrRoute = 0;
	int currDirection = 0;
	int currX = _start.x;
	int currY = _start.y;
	vector<Point> vp;
	int **map;
	int n = _grid.GetHeight();
	int m = _grid.GetWidth();
	map = new int *[m];
	for(int i = 0; i <m; i++){
		map[i] = new int[n];
	}

	for (int y = 0; y < _grid.GetHeight(); y++) {
		for (int x = 0; x < _grid.GetWidth(); x++) {
			int pix = _grid.GetValue(y,x);
			map[x][y] = pix;
		}
	}

	for (int i = 0; i < route.size(); i++) {
		char c = route.at(i);
		currDirection = atoi(&c);

		if (previusDirection != currDirection) {
			vp.push_back(Point(currX, currY));
			countCurrRoute = 0;
			previusDirection = currDirection;
		}
		else if(previusDirection == currDirection){
			if (countCurrRoute == 3){
				vp.push_back(Point(currX, currY));
				countCurrRoute = 0;
			}
			else{
				countCurrRoute++;
			}
		}

		switch (currDirection) {
			// Right
			case (0):
				currX += 1;
				break;
			// Down-Right
			case (1):
				currY += 1;
				currX += 1;
				break;
			// Down
			case (2):
				currY += 1;
				break;
			// Down-Left
			case (3):
				currY += 1;
				currX -= 1;
				break;
			// Left
			case (4):
				currX -= 1;
				break;
			// Up-Left
			case (5):
				currY -= 1;
				currX -= 1;
				break;
			// Up
			case (6):
				currY -= 1;
				break;
			// Up-Right
			case (7):
				currY -= 1;
				currX += 1;
				break;
			default:
				break;
			}
		map[currX][currY] = 3;
	}
	for (int i = 0; i < vp.size(); ++i) {
		vp[i].Print();
	}

	int mapX;
	int mapY;
	for (int i = 0; i < vp.size(); ++i) {
		mapX = ((Point)vp[i]).x;
		mapY = ((Point)vp[i]).y;
		map[mapX][mapY] = 2;
//			std::cout << ((Point)vp[i]).GetX() << ' ' << ((Point)vp[i]).GetY() << std::endl;
	}
	for(int j = 0; j <n; j++){
		for(int i = 0; i <m; i++){
			if(map[i][j] == 0)
			std::cout<< ".";
			else if (map[i][j] == 1)
				std::cout<< "0";
			else if (map[i][j] == 2)
				std::cout<< "W";
			else if (map[i][j] == 3)
				std::cout<< "R";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
