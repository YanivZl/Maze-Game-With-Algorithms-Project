#pragma once
#include <vector>
#include "Maze2D.h"

class MazeCompressor
{
public:
	std::string Compress(const Maze2D& maze);
	Maze2D Depress(std::string str);
};