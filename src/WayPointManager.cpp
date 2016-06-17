/*
 * wayPointManager.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: user
 */
#include <iostream>
#include <vector>
#include "WayPointManager.h"
#include "Point.h"
#include <math.h>

using namespace std;
WayPointManager::WayPointManager(Grid grid) {
	_grid = grid;
}

void WayPointManager::getWayPoint(){
	AStar a(_grid);
		string route = a.getValue();
		int countCurrRoute = 0;
		int currDirection = 0;
		int currX = 12;
		int currY = 25;
		vector<Point> vp;
//

		//


		for(int i = route.size() -1; i >= 0; i--) {
			char c =route.at(i);
			int j=atoi(&c);
			switch(j) {
				case (0):
					currX -= 1;
					break;
				case (1):
					currY -= 1;
					currX -= 1;
					break;
				case (2):
					currY -= 1;
					break;
				case (3):
					currY -= 1;
					currX += 1;
					break;
				case (4):
					currX += 1;
					break;
				case (5):
					currY += 1;
					currX += 1;
					break;
				case (6):
					currY += 1;
					break;
				case (7):
					currY += 1;
					currX -= 1;
					break;
				default:
					break;
			}

			if (currDirection != j){
				currDirection = j;
//				cout << currDirection;
//				countCurrRoute++;
//			} else if(currDirection == j){
//				countCurrRoute++;
//			} else if(currDirection != j){
//				int calcRoute = round(countCurrRoute / 2);
//
//
//				currDirection = j;
//				countCurrRoute = 1;
				vp.push_back(Point(currX, currY));
//			} else{
//				cout << "Not shouled enter here";
//			}
//			cout << (route[i]);

		}
		}
		for(int i=0; i<vp.size(); ++i){
					  std::cout << ((Point)vp[i]).GetX() << ' ' << ((Point)vp[i]).GetY() << std::endl;
				}

}
