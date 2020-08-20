#include "Controller.h"
#include "Maze2d.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::InitliizeCommand(const std::string& str)
{
    std::vector<std::string> commands;
    std::string word = "";
    for (const auto Tav : str)
    {
        if (Tav != ' ')
        {
            word = word + Tav;
}
        else
        {
            commands.push_back(word);
            word = "";
        }
    }
    commands.push_back(word);
    Args = commands;
}
