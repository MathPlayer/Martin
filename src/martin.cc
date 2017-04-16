#include "Board.h"
#include "UICommunication.h"

#include <iostream>
#include <cstdlib>

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
  int ret;

  Board *b = new Board();
  std::cout << *b << std::endl;

  ret = initCommunication();
  if (0 != ret) {
    std::cerr << "Init communication failed: " << ret << std::endl;
    std::exit(ret);
  }

  return 0;
}
