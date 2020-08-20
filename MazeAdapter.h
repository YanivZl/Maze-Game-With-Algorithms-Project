#pragma once
#include "Searchable.h"
#include "Maze2D.h"


#define MANHATTAN_DISTANCE (x1 , y1 , x2, y2) (abs(x2 - x1) + abs(y2 - y1))
#define AIR_DISTANCE (x1, y1, x2, y2) (sqrt(pow(x2 - x1) + pow(y2 - y1)))

class MazeAdapter
{
public:
	Searchable<Position>* getSearchableMaze(const Maze2D& maze);
	void insertSolutionToMaze(Maze2D& maze , std::vector<Node<Position>*> solution);
};
