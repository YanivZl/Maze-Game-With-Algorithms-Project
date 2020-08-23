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
#include <fstream>
//#include "MazeCompressation.h"
#include "MazeCompressor.h"
#include "BFS.h"
#include "MazeAdapter.h"
#include "Astar2D.h"

namespace fs = std::experimental::filesystem;
static std::vector<std::pair<std::string, Maze2D >> Mymazes;
typedef std::vector<Node<Position>*> Solution;
static std::map<std::string , std::pair<Maze2D,Solution*>> Mazes;
static std::map<Maze2D , Solution> cache;

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
        std::string str;
        for (std::string s : args)
        {
            if (s == "dir")
                continue;
            str += s + " ";
        }
        str.pop_back();
        const fs::path Path = str;
        for (auto itEntry = fs::recursive_directory_iterator(Path);
            itEntry != fs::recursive_directory_iterator();
            ++itEntry)
        {
            const auto filenameStr = itEntry->path().filename().string();
            std::cout << std::setw((int)itEntry.depth() * (int)3) << "";
            std::cout << "dir:  " << filenameStr << '\n';
        }
        std::cout << std::endl;
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
        if (Mazes.find(args[1]) != Mazes.end())
        {
            std::cout << "The name '" + args[1] + "' is already taken." << std::endl;
            return 1;
        }
        Maze2D Maze;
        Maze2DGenerator* Gen;
        if (args[2] == "prim")
            Gen = new MyMaze2dGenerator();
        else if (args[2] == "random")
            Gen = new SimpleMaze2dGenerator();
        else
            return 1;
        Maze = Gen->generate(std::stoi(args[3]), std::stoi(args[4]));
        std::cout << "Maze '" + args[1] + "' is generated." << std::endl;
        Mazes[args[1]] = std::make_pair(Maze , nullptr);
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
        //bool exsist = false;
        if(Mazes.find(args[1]) != Mazes.end()) // maze exsists in map.
        {
            std::cout << "\nThe maze under name '" + args[1] + "':\n\n" << BOLDWHITE;
            std::cout << Mazes[args[1]].first;
        }
        else
            std::cout << "\nMaze '" + args[1] + "' not exsist." << std::endl;
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
         Maze2D Maze;
         if (Mazes.find(args[1]) != Mazes.end()) // maze exsists in map.
         {
             MazeCompressor compressor;
             std::ofstream out_file;
             out_file.open(args[2], std::ios::app);
             if (!out_file.is_open())
             {
                 std::cout << "The file '" + args[2] + "' is not exsist.";
                 return 1;
             }
             std::string compressed_maze = compressor.Compress(Mazes[args[1]].first);
             out_file << args[1] << "\n" << compressed_maze << "\nS ";
             if (Mazes[args[1]].second != nullptr)
             {
                 for (auto s : *Mazes[args[1]].second)
                     out_file << s ->getNode() << " ";
             }
             out_file << "\n";
             out_file.close();
             std::cout << "Maze '" + args[1] + "' saved succesfully to '" + args[2] +"'\n";
         }
         else
             std::cout << "Maze '" + args[1] + "' not exsist." << std::endl;
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
        std::ifstream in_file;
        in_file.open(args[1]);
        if (!in_file.is_open())
        {
            std::cout << "The file '" + args[1] + "' is not exsist.";
            return 1;
        }
        std::string line;
        Maze2D maze;
        MazeCompressor compressor;
        while (!in_file.eof())
        {
            std::getline(in_file , line);
            if (!line.compare(args[2]))
            {
                std::getline(in_file, line);
                maze = compressor.Depress(line);
                std::getline(in_file, line);
                if (line.compare("S "))
                    Mazes[args[2]] = std::make_pair(maze, nullptr);
                else
                {
                    Solution* s = new Solution;
                    while (!line.empty())
                    {
                        std::string temp = line.substr(0, line.find(" "));
                        int x = std::atoi(line.substr(line.find("(") + 1, line.find(",") - 1).c_str());
                        int y = std::atoi(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1).c_str());
                        s -> push_back(new Node<Position>(Position(x, y)));
                        line = line.substr(line.find(" ") + 1, line.size() - line.find(" "));
                    }
                    Mazes[args[2]] = std::make_pair(maze, s);
                }
                std::cout << "Maze '" + args[2] + "' loaded succesfully from '" + args[1] + "'\n";
                return 1;
            }
        }
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
        if (Mazes.find(args[1]) != Mazes.end()) // maze exsists in map.
        {
            //std::cout << Mazes[args[1]].first;
            //int mazeSize = std::typeof;x
            int mazeWidth = Mazes[args[1]].first.getWidth();
            int mazehight = Mazes[args[1]].first.getHeight();
            auto temp = Mazes[args[1]].first.getMaze();
            int sizeCell = sizeof(temp[0][0]);
            int totalSize = mazehight * mazeWidth * sizeCell;
            std::cout << "The maze takes " << BOLDCYAN << totalSize << BOLDWHITE << " bits of the memory" << std::endl;
        }
        else
            std::cout << "Maze '" + args[1] + "' not exsist." << std::endl;

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

        if (Mazes.find(args[1]) != Mazes.end()) // maze exsists in map.
        {
            MazeAdapter adapter;
            Searchable<Position>* searchable_maze = adapter.getSearchableMaze(Mazes[args[1]].first);
            Solution* s = new std::vector<Node<Position>*>;
            if (args[2] == "bfs" || args[2] == "BFS")
            {
                BFS<Position> bfs;
                *s = bfs.search(searchable_maze);
                Mazes[args[1]].second = s;
                std::cout << "Done bfs on the maze " << BOLDCYAN + args[1] << BOLDWHITE << std::endl;
                
            }
            else if (args[2] == "astar" || args[2] == "Astar" || args[2] == "a*" || args[2] == "A*")
            {
                AStar2D<Position> a;
                *s = a.search(searchable_maze);
                Mazes[args[1]].second = s;
                std::cout << "Done A* on the maze " << BOLDCYAN + args[1] << BOLDWHITE << std::endl;
            }
            else
                std::cout << "algorithm unknown.";
        }
        else
            std::cout << "Maze '" + args[1] + "' not exsist.";
        return 1;

    }
};

/*------------------------------------------------------------------------*/
class solutionCommand : public Command
{
public:
    solutionCommand() {}
    int run(std::vector<std::string> args)
    {
        if (Mazes.find(args[1]) != Mazes.end()) // maze exsists in map.
        {
            if(Mazes[args[1]].second != nullptr)
            {
                MazeAdapter adapter;
                Maze2D temp_maze = Mazes[args[1]].first;
                adapter.insertSolutionToMaze(temp_maze, *Mazes[args[1]].second);
                std::cout << "Maze '" + args[1] + "' solution:\n" << temp_maze;
            }
            else
                std::cout << "Maze '" + args[1] + "' not solved yet.\n";
        }
        else
            std::cout << "Maze '" + args[1] + "' not exsist.";
        return 1;
    }
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