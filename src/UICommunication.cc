#include "UICommunication.h"

#include <iostream>
#include <string>

static std::string read_command()
{
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
}

static void write_command(const std::string &command)
{
    std::cout << command << std::endl;
    // TODO: flush stdout
}

int init_communication()
{
    std::string received_command = read_command();
    if (0 == received_command.compare(UI_MODE_UCI)) {
        // TODO: send uci options
    } else if (0 == received_command.compare(UI_MODE_XBOARD)) {
        // TODO: send xboard features conforming to protocol version 2
    } else {
        return EINVAL;
    }
    return 0;
}
