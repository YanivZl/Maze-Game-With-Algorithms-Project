#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <Windows.h>
#include "Position.h"

#define Horizonal 0
#define Vertical 1


class Maze2D
{
	char** _maze;
	int _width;
	int _height;
	
public:
	Maze2D() : _maze(nullptr), _width(NULL) , _height(NULL) {};
	Maze2D(int row, int column);
	Maze2D(const Maze2D& maze);
	int getWidth() const { return _width; };
	int getHeight() const { return _height; };
	char** getMaze() const { return _maze; };
	void setMaze(char** maze);
	void printMaze() const { std::cout << *this; };
	friend std::ostream& operator<<(std::ostream& out, const Maze2D& maze);
	Position getStartPosition() const;
	std::string getPossibleMoves(const Position& p) const;
	Position getGoalPosition();
	void printEmptyMaze(const Maze2D& maze) const;
	bool isSolved();
};

class Maze2DGenerator
{
protected:
	Maze2D _maze;
public:
	virtual Maze2D generate(int row, int column) = 0;
	virtual std::string measureAlgorithmTime(int row, int column) = 0;
};

class Maze : public Maze2DGenerator
{
public:
	virtual Maze2D generate(int row, int column) = 0;
	virtual std::string measureAlgorithmTime(int row, int column);
};


class SimpleMaze2dGenerator : public Maze
{
public:
	Maze2D generate(int row, int column);
private:
	void Divide(int row_start, int row_end, int col_start, int col_end, bool direction, Maze2D& maze);
};

class MyMaze2dGenerator : public Maze
{
public:
	Maze2D generate(int row, int column);
};