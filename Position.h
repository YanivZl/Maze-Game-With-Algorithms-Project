#pragma once
#include <iostream>

class Position
{
private:
	int _x;
	int _y;
public:
	Position() :_x(NULL), _y(NULL) {};
	Position(int x, int y) : _x(x), _y(y) {};
	int getX() const { return _x; };
	int getY() const { return _y; };
	Position opposite(const Position& p)
	{
		if (this->_x == p._x)
			return this->_y == p._y + 1 ? Position(this->_x, this->_y + 1) : Position(this->_x, this->_y - 1);
		return this->_x == p._x + 1 ? Position(this->_x + 1, this->_y) : Position(this->_x - 1, this->_y);
	};
	friend std::ostream& operator<<(std::ostream& out, const Position& p) { out << "( " << p._x << " , " << p._y << " )"; return out; };
	bool operator==(const Position& p)
	{
		return _x == p._x && _y == p._y ? true : false;
	}

	std::vector<int> getArguments() const
	{
		std::vector<int> vec;
		vec.push_back(_x);
		vec.push_back(_y);
		return vec;
	}
};