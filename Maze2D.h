#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <Windows.h>
#include "Position.h"

enum Arrows { Arrow = 224, Up = 72, Down = 80, Left = 75, Right = 77 };


class Maze2D
{
	char** _maze;
	int _width;
	int _height;
	
public:
	Maze2D() : _maze(nullptr), _width(NULL) , _height(NULL) {};
	Maze2D(int row, int column);
	int getWidth() const { return _width; };
	int getHeight() const { return _height; };
	char** getMaze() const { return _maze; };
	void setMaze(char** maze);
	void printMaze() const { std::cout << *this; };
	friend std::ostream& operator<<(std::ostream& out, const Maze2D& maze);
	Position getStartPosition() const;
	std::string getPossibleMoves(const Position& p) const;
	Position getGoalPosition();
};

class Maze2DGenerator
{
protected:
	Maze2D _maze;
public:
	virtual Maze2D genarate(int row, int column) = 0;
	virtual std::string measureAlgorithmTime(int row, int column) = 0;
};

class Maze : public Maze2DGenerator
{
public:
	virtual Maze2D genarate(int row, int column) = 0;
	virtual std::string measureAlgorithmTime(int row, int column);
};

class MyMaze2dGenerator : public Maze
{
public:
	Maze2D genarate(int row, int column);
};