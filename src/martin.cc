#include "UICommunication.h"

#include <iostream>

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
    std::string ui_mode = read_command();
    std::cout << "mode is: " << ui_mode << std::endl;
    return 0;
}
