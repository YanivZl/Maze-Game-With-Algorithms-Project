#include "MazeCompressor.h"

std::string MazeCompressor::Compress(const Maze2D& maze)
{
	std::string str;
	std::string extended_str;
	char** temp_maze = maze.getMaze();
	for (int i = 0; i < maze.getHeight(); i++)
		for (int j = 0; j < maze.getWidth(); j++)
			extended_str += temp_maze[i][j];
	char temp_char = '\0';
	int counter = 0;
	str += std::to_string(maze.getHeight()) + " " + std::to_string(maze.getWidth());
	for (char c : extended_str)
	{
		if (temp_char != c)
		{
			if (temp_char != '\0')
			{
				str += " ";
				str += temp_char;
				str += std::to_string(counter);
			}
			counter = 1;
			temp_char = c;
		}
		else
			counter++;
	}
	str += " ";
	str += temp_char;
	str += std::to_string(counter);
	return str;
}
Maze2D MazeCompressor::Depress(std::string str)
{
	
	int height = (int)std::atoi(str.substr(0 , str.find(" ")).c_str());
	str = str.substr(str.find(" ") + 1, str.size() - str.find(" "));
	int width = std::atoi(str.substr(0, str.find(" ")).c_str());
	str = str.substr(str.find(" ") + 1, str.size() - str.find(" "));
	Maze2D* maze = new Maze2D(height , width);
	std::string extended_str;
	while (1)
	{
		std::string temp_str = str.substr(1, str.find(" "));
		for (int i = 0; i < std::atoi(temp_str.c_str()); i++)
			extended_str += str[0];
		if (str.find(" ") == str.npos)
			break;
		str = str.substr(str.find(" ") + 1, str.size() - str.find(" "));
	}
	char** temp_maze = maze->getMaze();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			temp_maze[i][j] = extended_str[i * height + j];
	return *maze;
}