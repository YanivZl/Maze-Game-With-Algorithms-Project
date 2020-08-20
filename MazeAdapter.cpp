#include "MazeAdapter.h"

Searchable<Position>* MazeAdapter::getSearchableMaze(const Maze2D& maze)
{
	Searchable<Position>* searchable_maze = new Searchable<Position>;
	std::vector<Node<Position>>* nodes = searchable_maze ->getNodes();
	for (int i = 0; i < maze.getHeight(); i++)
		for (int j = 0; j < maze.getWidth(); j++)
			nodes -> push_back(Node<Position>(Position(j , i)));
	searchable_maze ->setNodes(*nodes);
	char** matrix = maze.getMaze();
	for (int i = 0; i < maze.getHeight(); i++)
		for (int j = 0; j < maze.getWidth(); j++)
		{
			Node<Position>* pos = &(nodes ->at(i * maze.getHeight() + j));
			if (matrix[i][j] == 'S')
			{
				searchable_maze ->setStartNode(i * maze.getHeight() + j);
			}
			if (matrix[i][j] == 'E')
			{
				searchable_maze ->setGoalNode(i * maze.getHeight() + j);
			}
			for(int k = -1; k <= 1; k++)
				for (int l = -1; l <= 1; l++)
				{
					if((l == 0 && k == 0) || (l != 0 && k != 0) )
						continue;
					if (i+k < 0 || i+k > maze.getHeight() - 1 || j+l < 0 || j+l > maze.getWidth() - 1)
						continue;
					if(matrix[i+k][j+l] == '1')
						pos ->appendChild(&(searchable_maze ->getNodes()->at((i+k) * maze.getHeight() + j+l)) , INT_MAX);
					else
						pos->appendChild(&(searchable_maze ->getNodes() ->at((i + k) * maze.getHeight() + j + l)), 1);

				}
			nodes->at(i * maze.getHeight() + j) = *pos;
		}
	searchable_maze ->setNodes(*nodes);
	return searchable_maze;
}

void MazeAdapter::insertSolutionToMaze(Maze2D& maze , std::vector<Node<Position>*> solution)
{
	char** matrix = maze.getMaze();
	for (unsigned int i = 0; i < solution.size(); i++)
	{ 
		if (matrix[solution[i]->getNode().getY()][solution[i]->getNode().getX()] == 'S' || matrix[solution[i]->getNode().getY()][solution[i]->getNode().getX()] == 'E')
			continue;
		matrix[solution[i]->getNode().getY()][solution[i]->getNode().getX()] = '*';
	}
	maze.setMaze(matrix);
}
