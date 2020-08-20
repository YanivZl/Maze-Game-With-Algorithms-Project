#pragma once
#include "Maze2D.h"
#include "Command.h"
#include <vector>
#include <map>


class Controller
{
public:
    Controller();
    ~Controller();
    virtual void InitliizeCommand(const std::string& str) = 0;
protected:
    std::map<std::string, Command*> Commands;
    std::vector<std::string> Args;
};