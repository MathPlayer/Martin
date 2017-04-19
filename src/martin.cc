#include "Board.h"
#include "UICommunication.h"

#include <iostream>
#include <cstdlib>

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
  int ret;

  Board *b = new Board();
  std::cout << *b << std::endl;

  UICommunication *c = new UICommunication();
  ret = c->MainLoop();
  if (ret) {
    std::cerr << "MainLoop exit with error code: " << ret << std::endl;
    std::exit(ret);
  }

  return 0;
}
