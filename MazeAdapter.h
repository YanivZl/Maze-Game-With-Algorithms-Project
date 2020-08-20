#pragma once
#include "Searchable.h"
#include "Maze2D.h"


#define MANHATTAN_DISTANCE "manhattan"
#define AIR_DISTANCE "air"

class MazeAdapter
{
public:
	Searchable<Position>* getSearchableMaze(const Maze2D& maze);
	void insertSolutionToMaze(Maze2D& maze , std::vector<Node<Position>*> solution);
};
