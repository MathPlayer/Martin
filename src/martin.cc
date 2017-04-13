#include "UICommunication.h"

#include <iostream>
#include <cstdlib>

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
    int ret;

    ret = init_communication();
    if (0 != ret) {
        std::cerr << "Init communication failed: " << ret << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return 0;
}
