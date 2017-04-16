#include "UICommunication.h"
#include "Common.h"

#include <cerrno>
#include <iostream>
#include <string>

#define UI_MODE_UCI	"uci"
#define UI_MODE_XBOARD	"xboard"

static const char * const xboard_features[] = {
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

static std::string readCommand()
{
  std::string ret;
  std::getline(std::cin, ret);
  return ret;
}

static void writeCommand(const std::string &command)
{
  std::cout << command << std::endl;
  // TODO: flush stdout
}

static int negociateXboardFeatures()
{
  const int N = sizeof(xboard_features) / sizeof(xboard_features[0]);
  for (int i = 0; i < N; i++) {
    writeCommand(xboard_features[i]);
    std::string ret = readCommand();
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

int initCommunication()
{
  std::string received_command = readCommand();
  int ret = 0;
  if (received_command == UI_MODE_UCI) {
    // TODO: send uci options
  } else if (received_command == UI_MODE_XBOARD) {
    ret = negociateXboardFeatures();
  } else {
    return EINVAL;
  }
  return ret;
}
