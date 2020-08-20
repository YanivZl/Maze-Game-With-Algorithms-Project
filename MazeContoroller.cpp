#include "MazeContoroller.h"

MazeContoroller::MazeContoroller()
{
    Commands["dir"] = new dirCommand();
    Commands["generate_maze"] = new generateCommand();
    Commands["display"] = new displayCommand();
    Commands["save_maze"] = new saveCommand();
    Commands["load_maze"] = new loadCommand();
    Commands["maze_size"] = new sizeCommand();
    Commands["file_size"] = new fsizeCommand();
    Commands["solve"] = new solveCommand();
    Commands["display_solution"] = new solutionCommand();
    Commands["exit"] = new exitCommand();
}

MazeContoroller::~MazeContoroller()
{
}

void MazeContoroller::InitliizeCommand(const std::string& str)
{
    std::vector<std::string> commands;
    std::string word = "";
    for (auto Tav : str)
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

    if (Commands[commands[0]]) {
        Commands[commands[0]]->run(commands);
    }
}
