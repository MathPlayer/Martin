#include "UICommunication.h"
#include "Common.h"

#include <cerrno>
#include <iostream>
#include <string>

#define UI_MODE_UCI     "uci"
#define UI_MODE_XBOARD  "xboard"

const char * const UICommunication::xboard_features[] = {
#ifdef DEBUG
  "feature debug=1",                  // show debug messages
#endif
  "feature sigint=0",                 // do not use SIGINT
  "feature myname=\""ENGINE_NAME"\"", // engine name
  "feature san=0",                    // use coordinate notation
  "feature variants=\"normal\"",      // play only standard chess
  "feature ping=0",                   // do not use ping
  "feature analyze=0",                // do not use analyze
  "feature done=1"                    // end of features
};

std::string UICommunication::ReadCommand()
{
  std::string ret;
  std::getline(std::cin, ret);
#ifdef DEBUG
    std::cout << "# received command: " << ret << std::endl;
#endif
  return ret;
}

void UICommunication::WriteCommand(const std::string &command)
{
  std::cout << command << std::endl;
  // TODO: flush stdout
}

int UICommunication::NegociateXboardFeatures()
{
  const int N = sizeof(xboard_features) / sizeof(xboard_features[0]);
  for (int i = 0; i < N; i++) {
    WriteCommand(xboard_features[i]);
    std::string ret = ReadCommand();
    if (ret == "rejected") {
      std::cerr << "Error: command '" << xboard_features[i]
        << "' was rejected. Abort." << std::endl;
      return EINVAL;
    } else if (ret != "accepted") {
      std::cerr << "Error: command '" << xboard_features[i]
        << "' was not accepted. Abort." << std::endl;
      return EINVAL;
    }
  }
  return 0;
}

int UICommunication::MainLoop()
{
  std::string command;
  int exit_loop = 0;

  while (!exit_loop) {
    command = ReadCommand();
    if (command == "quit") {
      return 0;
    } else if (command == "xboard") {
      exit_loop = NegociateXboardFeatures();
      if (exit_loop) {
        std::cerr << "Xboard negociation failed" << std::endl;
      }
    } else {
      return EINVAL;
    }
  }
  return exit_loop;
}
