#include "UICommunication.h"

#include <iostream>
#include <string>

std::string read_command()
{
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
}

