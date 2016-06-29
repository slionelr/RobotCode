/*
* wayPointManager.cpp
*
*  Created on: Jun 10, 2016
*      Author: user
*/
#include <iostream>
#include <vector>
#include <math.h>

#include "WaypointsManager.h"

using namespace std;
WaypointsManager::WaypointsManager(Grid grid, Point start) {
	_grid = grid;
	_start = start;
}

std::vector<Point> WaypointsManager::GetWayPoints(std::string route) {
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
	bool isSecondChange = false;

	/////////////////////////////////////////////////////////////
	// TODO: Is it necessary? Don't we have this data already?
	for(int i = 0; i <m; i++){
		map[i] = new int[n];
	}

	for (int y = 0; y < _grid.GetHeight(); y++) {
		for (int x = 0; x < _grid.GetWidth(); x++) {
			int pix = _grid.GetValue(y,x);
			map[x][y] = pix;
		}
	}
	/////////////////////////////////////////////////////////////

	for (int i = 0; i < route.size(); i++) {
		char c = route.at(i);
		currDirection = atoi(&c);

		if (previusDirection != currDirection) {
			if(isSecondChange){
				vp.push_back(Point(currX, currY));
				isSecondChange=false;
			}
			else{
				if(i != route.size() - 1){
					int nextIndex = i+1;
					if(currDirection != atoi(&route.at(nextIndex))){
						isSecondChange = true;
					}
					else{
						vp.push_back(Point(currX, currY));
					}
				}
			}
			countCurrRoute = 0;
			previusDirection = currDirection;
		}
		else if(previusDirection == currDirection){
			if (countCurrRoute == 4){
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
		} // End Switch-Case

		map[currX][currY] = 3;
	} // End loop

	//Destination Point
	vp.push_back(Point(currX, currY));

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

	return vp;
}
