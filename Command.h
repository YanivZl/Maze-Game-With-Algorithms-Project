#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
//#include "Maze2dGenerator.h"
//#include "MyMaze2dGenerator.h"
//#include "SimpleMaze2dGenerator.h"
#include <Windows.h>
#include "Maze2d.h"
#include <experimental/filesystem>
#include <filesystem>
//#include "MazeCompressation.h"
#include "BFS.h"
#include "MazeAdapter.h"
#include "Astar2D.h"

namespace fs = std::experimental::filesystem;
static std::vector<std::pair<std::string, Maze2D >> Mymazes;
typedef std::vector<Node<Position>*> Solution;

class Command {
public:
    virtual int run(std::vector<std::string> args) = 0;
    //protected:
    //    std::vector<std::pair<std::string, Maze2D >> Mymazes;
};
/*------------------------------------------------------------------------*/
class dirCommand : public Command
{
public:
    dirCommand() {}
    int run(std::vector<std::string> args)
    {
        const fs::path Path = args[1];
        for (auto itEntry = fs::recursive_directory_iterator(Path);
            itEntry != fs::recursive_directory_iterator();
            ++itEntry)
        {
            const auto filenameStr = itEntry->path().filename().string();
            std::cout << std::setw(itEntry.depth() * 3) << "";
            std::cout << "dir:  " << filenameStr << '\n';
        }
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class generateCommand : public Command
{
public:
    generateCommand() {}
    int run(std::vector<std::string> args)
    {
        Maze2D Maze;
        Maze2DGenerator* Gen;
        if (args[2] == "prim")
            Gen = new MyMaze2dGenerator();
        else if (args[2] == "random")
            Gen = new SimpleMaze2dGenerator();
        else
            return 1;
        Maze = Gen->generate(std::stoi(args[3]), std::stoi(args[4]));
        std::cout << std::endl << Maze;
        Mymazes.push_back(std::make_pair(args[1], Maze));
        Sleep(100);
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class displayCommand : public Command
{
public:
    displayCommand() {}
    int run(std::vector<std::string> args)
    {

        for (std::vector<std::pair<std::string, Maze2D >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
        {
            if (iter->first == args[1])
            {
                std::cout << BOLDYELLOW << "The Maze " << BOLDCYAN + args[1] + BOLDYELLOW << " Was Already Generated \n";
                std::cout << "Here is your Maze: \n" << BOLDWHITE;
                std::cout << iter->second;
                break;
            }
        }
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class saveCommand : public Command
{
public:
    saveCommand() {}
    int run(std::vector<std::string> args)
    {
        /* Maze2D Maze;
         std::string mazeName = args[1];
         std::string fileName = args[2];
         int answer = 0;
         std::vector<std::pair<std::string, Maze2D >> mazes = Mymazes;
         for (std::vector<std::pair<std::string, Maze2D >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
         {
             if (iter->first == mazeName)
             {
                 Maze = iter->second;
                 answer = 1;
             }
         }
         if (answer == 0)
         {
             std::cout << BOLDRED << "The Maze " << BOLDCYAN << mazeName << BOLDRED << " Not exist" << BOLDWHITE << endl;
             return 1;
         }
         MazeCompressaiton Save(mazeName, fileName, Maze);
         Save.Compress();
         return 1;*/
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class loadCommand : public Command
{
public:
    loadCommand() {}
    int run(std::vector<std::string> args)
    {
        /*Maze2 Maze;
        std::string mazeName = args[2];
        std::string fileName = args[1];
        int answer = 0;
        std::vector<std::pair<std::string, Maze2d >> mazes = Mymazes;
        for (std::vector<std::pair<std::string, Maze2d >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
        {
            if (iter->first == mazeName)
            {
                Maze = iter->second;
                answer = 1;
            }
        }
        if (answer == 0)
        {
            cout << BOLDRED << "The Maze " << BOLDCYAN << mazeName << BOLDRED << " Not exist" << BOLDWHITE << endl;
            return 1;
        }
        MazeCompressaiton Load(mazeName, fileName, Maze);
        Load.Expansion();*/
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class sizeCommand : public Command
{
public:
    sizeCommand() {}
    int run(std::vector<std::string> args)
    {
        //Maze2d Maze;
        //std::string mazeName = args[2];
        //std::string fileName = args[1];
        //int answer = 0;

        //std::vector<std::pair<std::string, Maze2d >> mazes = Mymazes;
        //for (std::vector<std::pair<std::string, Maze2d >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
        //{
        //    if (iter->first == mazeName)
        //    {
        //        Maze = iter->second;
        //        answer = 1;
        //    }
        //}
        //if (answer == 0)
        //{
        //    cout << BOLDRED << "The Maze " << BOLDCYAN << mazeName << BOLDRED << " Not exist" << BOLDWHITE << endl;
        //    return 1;
        //}
        //else
        //{
        //    MazeCompressaiton Size(mazeName, fileName, Maze);
        //    Size.getExpansionSize();
        //}
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class fsizeCommand : public Command
{
public:
    fsizeCommand() {}
    int run(std::vector<std::string> args)
    {
        //Maze2d Maze;
        //std::string mazeName = args[2];
        //std::string fileName = args[1];
        //int answer = 0;

        //std::vector<std::pair<std::string, Maze2d >> mazes = Mymazes;
        //for (std::vector<std::pair<std::string, Maze2d >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
        //{
        //    if (iter->first == mazeName)
        //    {
        //        Maze = iter->second;
        //        answer = 1;
        //    }
        //}
        //if (answer == 0)
        //{
        //    cout << BOLDRED << "The Maze " << BOLDCYAN << mazeName << BOLDRED << " Not exist" << BOLDWHITE << endl;
        //    return 1;
        //}
        //MazeCompressaiton Size(mazeName, fileName, Maze);
        //Size.getCompressedSize();
        return 1;
    }
};
/*------------------------------------------------------------------------*/
class solveCommand : public Command
{
public:
    solveCommand() {}
    int run(std::vector<std::string> args)
    {
        if (args[2] == "bfs" || args[2] == "BFS")
        {
            for (std::vector<std::pair<std::string, Maze2D >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
            {
                if (iter->first == args[1])
                {
                    MazeAdapter adapter;
                    Searchable<Position>* searchable_maze = adapter.getSearchableMaze(iter->second);
                    BFS<Position> bfs;
                    Solution s = bfs.search(searchable_maze);
                    Maze2D temp_maze = iter->second;
                    adapter.insertSolutionToMaze(temp_maze, s);

                    std::cout << "Done bfs on the maze " << BOLDCYAN + args[1] << BOLDWHITE << std::endl;
                }
            }
        }
        else if (args[2] == "astar" || args[2] == "Astar" || args[2] == "a*" || args[2] == "A*")
        {
            for (std::vector<std::pair<std::string, Maze2D >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
            {
                if (iter->first == args[1])
                {
                    MazeAdapter adapter;
                    Searchable<Position>* searchable_maze = adapter.getSearchableMaze(iter->second);
                    AStar2D<Position> a;
                    Solution s = a.search(searchable_maze, MANHATTAN_DISTANCE);
                    Maze2D temp_maze = iter->second;
                    adapter.insertSolutionToMaze(temp_maze, s);

                    std::cout << "Done A* on the maze " << BOLDCYAN + args[1] << BOLDWHITE << std::endl;
                }
            }
        }

        //std::cout << "Fuck all bitches! - sizeCommand - solveCommand" << std::endl;
        return 1;
    }
private:
};
/*------------------------------------------------------------------------*/
class solutionCommand : public Command
{
public:
    solutionCommand() {}
    int run(std::vector<std::string> args)
    {
        for (std::vector<std::pair<std::string, Maze2D >>::const_iterator iter = Mymazes.begin(); iter != Mymazes.end(); iter++)
        {
            if (iter->first == args[1])
            {
                iter->second.printMaze();
            }
        }

        //std::cout << "Fuck all bitches! - solutionCommand" << std::endl;
        return 1;
    }
private:
};
/*------------------------------------------------------------------------*/
class exitCommand : public Command
{
public:
    exitCommand() {}
    int run(std::vector<std::string> args)
    {
        std::cout << "Thank you, see you next time!!\nBye Bye!!" << std::endl;
        exit(0);
        return 0;
    }
private:
};
/*------------------------------------------------------------------------*/