// PathPlanner.cpp
// http://en.wikipedia.org/wiki/A*
// Compiler: Dev-C++ 4.9.9.2
// FB - 201012256

#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>

#include "PathPlanner.h"

using namespace std;

// map of directions
const int dir = 8; // number of possible directions to go at any position
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

class node
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

public:
	node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10; //A*
	}

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i, int **map, int xdx, int ydy) // i: direction
	{
		int xax = 0;
		int yay = 0;
		bool isCloseToObstacle = false;
		level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);

		for (int i = 0; i < dir; i++)
		{
			xax = xdx + dx[i];
			yay = ydy + dy[i];
			if (xax >= 0 && yay >= 0) {
				if (map[xax][yay] == 1) {
					isCloseToObstacle = true;
				}
			}
			else {
				isCloseToObstacle = true;
			}
		}

		if (isCloseToObstacle) {
			level = level + 5;
		}

	}

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian Distance
		d = static_cast<int>(sqrt(xd*xd + yd*yd));

		// Manhattan distance
		//d=abs(xd)+abs(yd);

		// Chebyshev distance
		//d=max(abs(xd), abs(yd));

		return(d);
	}
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish, const int & m, const int & n,
	int  **closed_nodes_map, int  **open_nodes_map, int **map, int **dir_map)
{
	static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static node* n0;
	static node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y < m; y++)
	{
		for (x = 0; x < n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map

											  // A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i, map, xdx, ydy);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy] > m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}


	return ""; // no route found
}



PathPlanner::PathPlanner(Grid grid, Point start, Point end) {
	_grid = grid;
	_start = start;
	_end = end;
}

string PathPlanner::GetPath() {
	int n = _grid.GetHeight();
	int m = _grid.GetWidth();
	int **map;
	int **closed_nodes_map; // map of closed (tried-out) nodes
	int **open_nodes_map; // map of open (not-yet-tried) nodes
	int **dir_map;

	map = new int *[m];
	closed_nodes_map = new int *[m];
	open_nodes_map = new int *[m];
	dir_map = new int *[m];

	for (int i = 0; i < m; i++) {
		map[i] = new int[n];
		closed_nodes_map[i] = new int[n];
		open_nodes_map[i] = new int[n];
		dir_map[i] = new int[n];
	}
	for (unsigned y = 0; y < _grid.GetHeight(); y++) {
		for (unsigned x = 0; x < _grid.GetWidth(); x++) {
			int pix = _grid.GetValue(y, x);
			map[x][y] = pix;
		}

	}

	srand(time(NULL));
	int xA, yA, xB, yB;
	//			    xB=12;yB=25;xA=60-1;yA=25-1;
	xA = _start.x; yA = _start.y; xB = _end.x; yB = _end.y;

	cout << "Map Size (X,Y): " << n << "," << m << endl;
	cout << "Start: " << xA << "," << yA << endl;
	cout << "Finish: " << xB << "," << yB << endl;
	// get the route
	clock_t start = clock();
	string route = pathFind(xA, yA, xB, yB, m, n, closed_nodes_map, open_nodes_map, map, dir_map);

	if (route == "") cout << "An empty route generated!" << endl;
	clock_t end = clock();
	double time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	cout << "Route:" << endl;
	cout << route << endl << endl;

	if (route.length() > 0)
	{
		int j; char c;
		int x = xA;
		int y = yA;
		map[x][y] = 2;
		for (unsigned i = 0; i < route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c);
			x = x + dx[j];
			y = y + dy[j];
			map[x][y] = 3;
		}
		map[x][y] = 4;

		// display the map with the route
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++) {
				if (map[x][y] == 0)
					cout << ".";
				else if (map[x][y] == 1)
					cout << "O"; //obstacle
				else if (map[x][y] == 4)
					cout << "F"; //start
				else if (map[x][y] == 3)
					cout << "R"; //route
				else if (map[x][y] == 2)
					cout << "S"; //finish
			}
			cout << endl;
		}
	}

	return route;
}
