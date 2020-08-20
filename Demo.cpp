#include "Demo.h"

#define MANHATTAN_DISTANCE "manhattan"
#define AIR_DISTANCE "air"

typedef std::vector<Node<Position>*> Solution;

void Demo::run()
{
	MazeAdapter adapter;
	MyMaze2dGenerator generator;
	Maze2D maze = generator.genarate(20	, 20);
	maze.printMaze();
	Searchable<Position>* searchable_maze = adapter.getSearchableMaze(maze);
	BFS<Position> bfs;
	//Solution s = bfs.search(searchable_maze);
	//adapter.insertSolutionToMaze(maze , s);
	//std::cout << std::endl;
	//maze.printMaze();
	std::cout << std::endl;
	AStar2D<Position> a;
	//Air distance
	Solution s = a.search(searchable_maze , MANHATTAN_DISTANCE);
	adapter.insertSolutionToMaze(maze, s);
	maze.printMaze();
	//a.fromHere(&searchable_maze ->getNodes() ->at(searchable_maze ->getStartNode()) , &searchable_maze->getNodes()->at(searchable_maze->getGoalNode()) , AIR_DISTANCE);
	//Manhattan distance
	//a.fromHere(&searchable_maze->getNodes()->at(searchable_maze->getStartNode()), &searchable_maze->getNodes()->at(searchable_maze->getGoalNode()), MANHATTAN_DISTANCE);

}