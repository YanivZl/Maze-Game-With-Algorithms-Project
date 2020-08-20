#include <iostream>
#include <string>
#include "MazeContoroller.h"
#include <conio.h>
#include "view.h"

class MazeView : public view
{
public:
    void help();
    //void printoptions(int selected);
    MazeView(std::ostream& out, std::istream& in) :view(out, in), exit(1)
    {
        con = new MazeContoroller();
    };
    void start()
    {
        while (exit != 0)
        {
            system("cls");
            help();
            std::string client_input;
            if (exit != 0)
            {
                getline(std::cin, client_input);
                con->InitliizeCommand(client_input);
                std::cout << "Press any key to continue...";
                _getch();
            }
        }
    }
private:
    int exit;
};



