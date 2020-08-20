#pragma once
#include <iostream>
#include <string>
#include "Controller.h"
#include <conio.h>

class view
{
public:
    virtual void start() = 0;
    view(std::ostream& out, std::istream& in) :_out(out), _in(in) {};
protected:
    std::ostream& _out;
    std::istream& _in;
    Controller* con;
};