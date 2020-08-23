// Maze_Game_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Maze2D.h"
#include "Demo.h"
#include"MazeView.h"

class TestMazeGenarator
{
public:
    TestMazeGenarator() {};

    void testMazeGenarator(Maze2DGenerator& mg)
    {
        std::cout << mg.measureAlgorithmTime(200, 200) << std::endl;
        std::cout << std::endl;
        Maze2D maze = mg.generate(30, 30);
        Position p = maze.getStartPosition();
        std::cout << p << std::endl;
        std::cout << maze.getPossibleMoves(p) << std::endl;
        std::cout << maze.getGoalPosition() << std::endl;
        std::cout << maze << std::endl;
    }
};

int main()
{
    system("mode 650");
    //TestMazeGenarator t;
    //MyMaze2dGenerator mg;
    //t.testMazeGenarator(mg);
   // Demo d;
    //d.run();
    MazeView(std::cout, std::cin).start();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
