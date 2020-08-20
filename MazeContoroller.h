#pragma once
#include "Controller.h"



class MazeContoroller : public Controller
{
public:
	MazeContoroller();
	~MazeContoroller();
	virtual void InitliizeCommand(const std::string& str);

private:
	Maze2D* _myMaze;
};


