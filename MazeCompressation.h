#pragma once
#include "Compressaition.h"
#include "Maze2D.h"
#include <conio.h>
#include <Windows.h>



class MazeCompressaiton : public Compressaiton
{
private:
	Maze2D maze;
	string maze_Name;
	string file_Name;
	ofstream myfile_write;
	ifstream myfile_read;

	char** charMaze;
	vector<int> BigArray;
	vector<int> compressionarray;
	vector<int> expansionarray;
	vector<vector<int>> expansionMaze;


public:
	MazeCompressaiton(string mazeName, string fileName, Maze2D get_maze) : maze_Name(mazeName), maze(get_maze), file_Name(fileName)
	{
		// Compression - Guide
		// '0' =  0	= Free
		// '1' =  1	= Wall
		// 'S' = -2 = Start
		// 'E' = -3 = End
		charMaze = maze.getMaze();
		int counterArray = 0;
		for (int i = 0; i < maze.getHeight(); i++)
		{
			for (int j = 0; j < maze.getWidth(); j++, counterArray++)
			{
				if (charMaze[i][j] == '0')
					BigArray.push_back(0);
				else if (charMaze[i][j] == '1')
					BigArray.push_back(1);
				else if (charMaze[i][j] == 'S')
					BigArray.push_back(-2);
				else 
					BigArray.push_back(-3);
			}
		}	
		vector<vector<int> > vec(maze.getHeight());
		for (int i = 0; i < maze.getHeight(); i++)
		{
			vec[i] = vector<int>(maze.getWidth());
			for (int j = 0; j < maze.getWidth(); j++)
				vec[i][j] = -1;
		}
		expansionMaze = vec;
	}
	MazeCompressaiton(string mazeName, Maze2D get_maze) : maze_Name(mazeName) , maze(get_maze)
	{
		charMaze = maze.getMaze();
		int counterArray = 0;
		for (int i = 0; i < maze.getHeight(); i++)
		{
			for (int j = 0; j < maze.getWidth(); j++, counterArray++)
			{
				if (charMaze[i][j] == '0')
					BigArray.push_back(0);
				else if (charMaze[i][j] == '1')
					BigArray.push_back(1);
				else if (charMaze[i][j] == 'S')
					BigArray.push_back(-2);
				else
					BigArray.push_back(-3);
			}
		}
		vector<vector<int> > vec(maze.getHeight());
		for (int i = 0; i < maze.getHeight(); i++)
		{
			vec[i] = vector<int>(maze.getWidth());
			for (int j = 0; j < maze.getWidth(); j++)
				vec[i][j] = -1;
		}
		expansionMaze = vec;
	}
	~MazeCompressaiton() {}

	void Compress();
	virtual void Expansion();
	virtual int getCompressedSize();
	virtual int getExpansionSize();

private:
	int IsMazeExistNew(string name, string FileName);
	void UpdateCompressedArray();
};
