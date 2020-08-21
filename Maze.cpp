#include "Maze2D.h"

Maze2D::Maze2D(int row, int column)
{
	_height = column;
	_width = row;
	_maze = new char* [column];
	for (int i = 0; i < column; i++)
		_maze[i] = new char[row];
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

//Maze2D SimpleMaze2dGenerator::genarate(int row, int column)
//{
//	srand((unsigned int)time(NULL));
//	Maze2D maze(row, column);
//	char** temp_maze = maze.getMaze();
//	for (int i = 0; i < column; i++)
//		for (int j = 0; j < row; j++)
//			temp_maze[i][j] = '0';
//	//Position start(0, rand() % row);
//	//Position end(column - 1 , rand() % row);
//	if(row > column)
//		Divide(0, column, 0, row, Horizonal, temp_maze);
//	else
//		Divide(0, column, 0, row, Vertical, temp_maze); //start by splitting vertically
//	maze.setMaze(temp_maze);
//	//temp_maze[start.getY()][start.getX()] = 'S';
//	//temp_maze[end.getY()][end.getX()] = 'E';
//	return maze;
//}		
//
//void SimpleMaze2dGenerator::Divide(int first_row, int last_row, int first_column, int last_column, bool direction, char** maze)
//{
//	if (last_row - first_row <= 2 || last_column - first_column <= 2)
//		return;
//	int wall_to_break;
//	int random_wall;
//	int random_gap;
//	if (direction) //Vertical
//	{
//		random_wall = rand() % (last_row - 2);
//		for (int i = first_column; i < last_column; i++)
//			maze[random_wall][i] = '1';
//		random_gap = rand() % last_column;
//		maze[random_wall][random_gap] = '0';
//		Divide(first_row, random_wall, first_column, last_column, Vertical, maze);
//		Divide(random_wall, last_row, first_column, last_column, Vertical, maze);
//	}
//	else
//	{
//		random_wall = rand() % (last_column - 2);
//		for (int i = first_row; i < last_row; i++)
//			maze[i][random_wall] = '1';
//		random_gap = rand() % last_row;
//		maze[random_gap][random_wall] = '0';
//		Divide(first_row, last_row, first_column, random_wall, Horizonal, maze);
//		system("CLS");
//		for (int i = 0; i < last_row; i++)
//		{
//			for (int j = 0; j < last_column; j++)
//				std::cout << maze[i][j];
//			std::cout << std::endl;
//		}
//		Divide(first_row, last_row, random_wall, last_column, Horizonal, maze);
//		system("CLS");
//		for (int i = 0; i < last_row; i++)
//		{
//			for (int j = 0; j < last_column; j++)
//				std::cout << maze[i][j];
//			std::cout << std::endl;
//		}
//	}
//	////system("CLS");
//	////for (int i = 0; i < last_row; i++)
//	////{
//	////	for (int j = 0; j < last_column; j++)
//	////		std::cout << maze[i][j];
//	////	std::cout << std::endl;
//	////}
//	//if (last_row - first_row <= 2 || last_column - first_column <= 2)
//	//	return;
//	//int wall_to_break;
//	//if (direction == Horizonal)
//	//{
//	//	// creating a vertical line of walls at a random position 
//	//	int seperator_col;
//	//	while (1) // get even random int from col_start to col_end
//	//	{
//	//		seperator_col = rand() % last_column;
//	//		if (seperator_col % 2 == 0)
//	//			break;
//	//	}
//	//	for (int i = first_row; i < last_row; i++) // insert walls line
//	//		maze[i][seperator_col] = '1';
//
//	//	while (1) // breaking a random wall in the previous random line
//	//	{
//	//		wall_to_break = rand() % last_row;
//	//		if (wall_to_break % 2 == 1)
//	//		{
//	//			maze[wall_to_break][seperator_col] = '0';
//	//			break;
//	//		}
//	//	}
//	//	
//	//	for (int i = 0; i < last_row; i++)
//	//	{
//	//		for (int j = 0; j < last_column; j++)
//	//		std::cout << maze[i][j];
//	//	std::cout << std::endl;
//	//	}
//	//	std::cout << std::endl;
//	//	//Recursively 
//	//	Divide(first_row, last_row, first_column, seperator_col, Vertical, maze);
//	//	//system("cls");
//	//	//cout << maze;
//	//	Divide(first_row, last_row, seperator_col, last_column, Vertical, maze);
//	//	//system("cls");
//	//	//cout << maze;
//	//}
//
//	//else // Vertical Dividing
//	//{
//	//	// creating an Horizonal line of walls at a random position 
//	//	int seperator_row;
//	//	while (1) // get paired random int from col_start to col_end
//	//	{
//	//		seperator_row = rand() % last_row;
//	//		if (seperator_row % 2 == 0)
//	//			break;
//	//	}
//	//	for (int i = first_column; i < last_column; i++) // insert walls column
//	//		maze[seperator_row][i] = '1';
//
//	//	// breaking a random wall
//	//	while (1) // get even random int from col_start to col_end
//	//	{
//	//		wall_to_break = rand() % last_column;
//	//		if (wall_to_break % 2 == 0)
//	//		{
//	//			maze[seperator_row][wall_to_break]= '0';
//	//			break;
//	//		}
//	//	}
//	//	for (int i = 0; i < last_row; i++)
//	//	{
//	//		for (int j = 0; j < last_column; j++)
//	//			std::cout << maze[i][j];
//	//		std::cout << std::endl;
//	//	}
//	//	std::cout << std::endl;
//	//	//Recursively 
//	//	Divide(first_row, seperator_row, first_column, last_column, Horizonal, maze);
//	//	/*system("cls");
//	//	cout << maze;*/
//	//	Divide(seperator_row, last_row, first_column, last_column, Horizonal, maze);
//	//	/*system("cls");
//	//	cout << maze;*/
//	//}
//	return;
//
//}


//Maze2D SimpleMaze2dGenerator::generate(int rows, int columns)
//{
//
//	Maze2D maze(rows, columns);
//
//	//maze.makeRandomEntryAndExit();
//	//maze.clearWalls();
//
//	int col = maze.getWidth();
//	int row = maze.getHeight();
//
//	if (row > col) // if there are more rows than columns 
//		Divide(0, row, 0, col, Horizonal, maze); //start by splitting horizonally
//	else
//		Divide(0, row, 0, col, Vertical, maze); //start by splitting vertically
//
//	//maze.resetVisited();
//	return maze;
//}
//
//
//void SimpleMaze2dGenerator::Divide(int row_start, int row_end, int col_start, int col_end, bool direction, Maze2D& maze)
//{
//	char** temp_maze = maze.getMaze();
//	if (row_end - row_start <= 2 || col_end - col_start <= 2)
//		return;
//	int wall_to_break;
//	if (direction == Vertical)
//	{
//		// creating a vertical line of walls at a random position 
//		int seperator_col = getExclusiveRandom(col_start, col_end, 0); // get paired random int from col_start to col_end
//		createWallsLine(row_start, row_end, seperator_col, Vertical, maze);
//
//		// breaking a random wall in the previous random line
//		wall_to_break = getExclusiveRandom(row_start, row_end, 1);
//		temp_maze[wall_to_break][seperator_col] = '0';
//		//maze.openThePath(wall_to_break, seperator_col);
//
//		//Recursively 
//		Divide(row_start, row_end, col_start, seperator_col, Horizonal, maze);
//		system("cls");
//		for (int i = 0; i < maze.getHeight(); i++)
//		{
//			for (int j = 0; j < maze.getWidth(); j++)
//				std::cout << temp_maze[i][j];
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//		//cout << maze;
//		Divide(row_start, row_end, seperator_col, col_end, Horizonal, maze);
//		system("cls");
//		for (int i = 0; i < maze.getHeight(); i++)
//		{
//			for (int j = 0; j < maze.getWidth(); j++)
//				std::cout << temp_maze[i][j];
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//		//cout << maze;
//	}
//
//	else // Horizonal Dividing ::
//	{
//		// creating an Horizonal line of walls at a random position 
//		int seperator_row = getExclusiveRandom(row_start, row_end, 0);
//		createWallsLine(col_start, col_end, seperator_row, Horizonal, maze);
//
//		// breaking a random wall
//		wall_to_break = getExclusiveRandom(col_start, col_end, 1);
//		temp_maze[seperator_row][wall_to_break] = '0';
//		//maze.openThePath(seperator_row, wall_to_break);
//
//		//Recursively 
//		Divide(row_start, seperator_row, col_start, col_end, Vertical, maze);
//		system("cls");
//		for(int i = 0 ; i < maze.getHeight() ; i++)
//		{
//			for (int j = 0; j < maze.getWidth(); j++)
//				std::cout << temp_maze[i][j];
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//		//cout << maze;
//		Divide(seperator_row, row_end, col_start, col_end, Vertical, maze);
//		system("cls");
//		for (int i = 0; i < maze.getHeight(); i++)
//		{
//			for (int j = 0; j < maze.getWidth(); j++)
//				std::cout << temp_maze[i][j];
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//		//cout << maze;
//	}
//	return;
//}
//
//
//int SimpleMaze2dGenerator::getExclusiveRandom(const int& min, const int& max, const bool& restriction)
//{
//	//restriction = 0 : EVEN,	restriction = 1: ODD
//
//	int val = rand() % max;
//	while (bool(val % 2) != restriction || val <= min)
//		val = rand() % max;
//	return val;
//}
//
//
//void SimpleMaze2dGenerator::createWallsLine(int itr, const int& end, const int& seperator, bool direction, Maze2D& maze)
//{
//	char** temp_maze = maze.getMaze();
//	while (itr++ < end - 1)
//		if (direction == Vertical)
//			temp_maze[itr][seperator] = '1';
//		else
//			temp_maze[seperator][itr] = '1';
//	maze.setMaze(temp_maze);
//}