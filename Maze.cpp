#include "Maze2D.h"

Maze2D::Maze2D(int row, int column)
{
	_height = column;
	_width = row;
	_maze = new char* [column];
	for (int i = 0; i < column; i++)
		_maze[i] = new char[row];
}

Maze2D::Maze2D(const Maze2D& maze)
{
	_height = maze._height;
	_width = maze._width;
	_maze = new char* [_height];
	for (int i = 0; i < _height; i++)
		_maze[i] = new char[_width];
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_maze[i][j] = maze._maze[i][j];
}

void Maze2D::setMaze(char** maze)
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_maze[i][j] = maze[i][j];
}


std::ostream& operator<<(std::ostream& out, const Maze2D& maze) 
{

	for (int i = 0; i < maze._width * 2 + 2; i++)
		out << "$";
	out << std::endl;
	for (int i = 0; i < maze._height; i++)
	{
		out << "$";
		for (int j = 0; j < maze._width; j++)
		{
			if (maze._maze[i][j] == '1')
				out << "##";
			else if (maze._maze[i][j] == '*')
				out << "**";
			else if (maze._maze[i][j] == 'S')
				out << "S ";
			else if (maze._maze[i][j] == 'E')
				out << "E ";
			else
				out << "  ";
		}
		out << "$" << std::endl;
	}
	for (int i = 0; i < maze._width * 2 + 2; i++)
		out << "$";
	out << std::endl;
	return out;
};


Position Maze2D::getStartPosition() const
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			if (_maze[i][j] == 'S')
				return Position(j, i);
	return Position();
}
std::string Maze2D::getPossibleMoves(const Position& p) const
{
	
	std::string str = "";
	if (p.getY() > _height - 1 && p.getX() <= 0)
		return str;
	if (!(p.getY() == 0))
		if (_maze[p.getY() - 1][p.getX()] != '1')
			str += "Up ";
	if (!(p.getY() >= _height - 1))
		if (_maze[p.getY() + 1][p.getX()] != '1')
			str += "Down ";
	if (!(p.getX() == 0))
		if (_maze[p.getY()][p.getX() - 1] != '1')
			str += "Left ";
	if (!(p.getX() >= _width - 1))
		if (_maze[p.getY()][p.getX() + 1] != '1')
			str += "Right ";
	return str;
}
Position Maze2D::getGoalPosition()
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			if (_maze[i][j] == 'E')
				return Position(j, i);
	return Position();
}

std::string Maze::measureAlgorithmTime(int row, int column)
{
	auto start = std::chrono::high_resolution_clock::now();
	generate(row , column);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	return "It takes " + std::to_string((double)duration.count() / 1000) + " sec to genarate " + std::to_string(column) + "x" + std::to_string(row) + " maze.";
}

Maze2D MyMaze2dGenerator::generate(int row, int column)
{
	// select random point and open as start node
	// get maze from Maze2d and initialize with walls
	Maze2D maze(row , column);
	char** temp_maze = maze.getMaze();
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			temp_maze[i][j] = '1';
	Position p(0, rand() % row);
	temp_maze[p.getY()][p.getX()] = '0';
	
	std::vector<std::pair<Position, Position>> wallList;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0 || i != 0 && j != 0)
				continue;
			if (!(p.getY() + i >= 0 && p.getY() + i <= column && p.getX() + j >= 0 && p.getX() + j <= row))
				continue;
			wallList.push_back(std::make_pair(Position(p.getX() + j , p.getY() + i), p));
		}

	Position last;
	while (!wallList.empty())
	{
  		int rand_next = rand() % wallList.size();
		std::pair<Position, Position> next_to_check(wallList[rand_next]);
		wallList.erase(wallList.begin() + rand_next);
		Position opposite_to_wall = next_to_check.first.opposite(next_to_check.second);
		if (opposite_to_wall.getY() < 0 || opposite_to_wall.getY() >= column || opposite_to_wall.getX() < 0 || opposite_to_wall.getX() >= row)
			continue;
		if (temp_maze[next_to_check.first.getY()][next_to_check.first.getX()] == '1')
		{
			if (temp_maze[opposite_to_wall.getY()][opposite_to_wall.getX()] == '1')
			{
				temp_maze[next_to_check.first.getY()][next_to_check.first.getX()] = '0';
				temp_maze[opposite_to_wall.getY()][opposite_to_wall.getX()] = '0';

				last = opposite_to_wall;

				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
					{
						if (i == 0 && j == 0 || i != 0 && j != 0)
							continue;
						if (opposite_to_wall.getY() + i < 0 || opposite_to_wall.getY() + i >= column || opposite_to_wall.getX() + j < 0 || opposite_to_wall.getX() + j >= row)
							continue;
						if (temp_maze[opposite_to_wall.getY() + i][opposite_to_wall.getX() + j] == '0') 
							continue;
						wallList.push_back(std::make_pair(Position(opposite_to_wall.getX() + j, opposite_to_wall.getY() + i), opposite_to_wall));
					}
			}
		}	
	}

	bool isLastColumnIsWall = 1;
	for (int i = 0; i < column; i++)
		if (temp_maze[i][row - 1] == '0')
		{
			isLastColumnIsWall = 0;
			break;
		}
	int columnToPushRandomE = isLastColumnIsWall ? row - 2 : row - 1;
	while (1)
	{
		int randRow = rand() % column;
		if (temp_maze[randRow][columnToPushRandomE] == '1')
			continue;
		temp_maze[randRow][columnToPushRandomE] = 'E';
		break;

	}
	temp_maze[p.getY()][p.getX()] = 'S';
	return maze;
}

Maze2D SimpleMaze2dGenerator::generate(int row, int column)
{
	Maze2D maze(row, column);
	char** temp_maze = maze.getMaze();
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			temp_maze[i][j] = '0';
	if (maze.getHeight() > maze.getWidth())
		Divide(0, maze.getWidth(), 0, maze.getHeight(), Vertical, maze);
	else
		Divide(0, maze.getWidth(), 0, maze.getHeight(), Horizonal, maze);
	Position start(0, rand() % row);
	Position goal(maze.getWidth() - 1, rand() % row);
	
	temp_maze[start.getY()][start.getX()] = 'S';
	temp_maze[goal.getY()][goal.getX()] = 'E';
	return maze;
}

void SimpleMaze2dGenerator::Divide(int first_column, int last_column, int first_row, int last_row, bool direction, Maze2D& maze)
{
	char** temp_maze = maze.getMaze();
	if (last_row - first_row <= 2 || last_column - first_column <= 2)
		return;
	if (direction) // Vertical - Insert a vertical wall and open a gap there , and divide horizontally.
	{
		int wall;
		while (1)
		{
			wall = first_column + rand() % (last_column - first_column - 1);
			wall == first_column ? wall++ : wall;
			if (wall % 2 == 0 || last_column - first_column == 2)
				break;
		}
		bool hasGap = false;
		for (int i = first_row; i < last_row; i++)
		{
			if(first_row > 0)
				if (i == first_row && temp_maze[first_row - 1][wall] == '0')
				{
					hasGap = true;
					continue;
				}
			if (last_row < maze.getWidth())
				if (i == last_row - 1 && temp_maze[last_row][wall] == '0')
				{
					hasGap = true;
					continue;
				}
			temp_maze[i][wall] = '1';
		}
		int gap;
		while(1)
		{
			gap = first_row + rand() % (last_row - first_row);
			if (gap % 2 == 1)
				break;
		}
		hasGap ? NULL : temp_maze[gap][wall] = '0';
		Divide(first_column, wall, first_row, last_row, Horizonal, maze);
		Divide(wall + 1, last_column, first_row, last_row, Horizonal, maze);
	}
	else // Horizontally - Insert a vertical wall and open a gap there , and divide Vertically.
	{
		int wall;
		while(1)
		{
			wall = first_row + rand() % (last_row - first_row - 1);
			wall == first_row ? wall++ : wall;
			if (wall % 2 == 0 || last_row - first_row == 2)
				break;
		}
		bool hasGap = false;
		for (int i = first_column; i < last_column; i++)
		{
			if (first_column > 0)
				if (i == first_column && temp_maze[wall][first_column - 1] == '0')
				{
					hasGap = true;
					continue;
				}
			if(last_column < maze.getHeight())
				if (i == last_column - 1 && temp_maze[wall][last_column] == '0')
				{
					hasGap = true;
					continue;
				}
			temp_maze[wall][i] = '1';
		}
		int gap;
		while (1)
		{
			gap = first_column + rand() % (last_column - first_column);
			if (gap % 2 == 1)
				break;
		}
		//temp_maze[wall][gap] = '0';
		hasGap ? NULL : temp_maze[wall][gap] = '0';
		Divide(first_column, last_column , first_row, wall, Vertical, maze);
		Divide(first_column, last_column, wall + 1, last_row, Vertical, maze);
	}
	return;
}


void Maze2D::printEmptyMaze(const Maze2D& maze) const
{
	for (int i = 0; i < maze._width * 2 + 2; i++)
		std::cout << "$";
	std::cout << std::endl;
	for (int i = 0; i < maze._height; i++)
	{
		std::cout << "$";
		for (int j = 0; j < maze._width; j++)
		{
			if (maze._maze[i][j] == '1')
				std::cout << "##";
			else if (maze._maze[i][j] == '*')
				std::cout << "  ";
			else if (maze._maze[i][j] == 'S')
				std::cout << "S ";
			else if (maze._maze[i][j] == 'E')
				std::cout << "E ";
			else
				std::cout << "  ";
		}
		std::cout << "$" << std::endl;
	}
	for (int i = 0; i < maze._width * 2 + 2; i++)
		std::cout << "$";
	std::cout << std::endl;
}

bool Maze2D::isSolved()
{
	int counter = 0;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			if (_maze[i][j] == '*')
			{
				counter++;
				break;
			}
		}
	}

	if (counter > 0)
		return true;

	return false;
}