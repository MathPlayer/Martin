#pragma once

#include <string>

/** Defined modes of interaction with an UI. */
#define UI_MODE_UCI     "uci"
#define UI_MODE_XBOARD  "xboard"

class UICommunication
{
  // TODO: add comments
  private:
    static const char * const xboard_features[];

    std::string mode;

    int NegociateXboardFeatures();
    std::string ReadCommand();
    void WriteCommand(const std::string &command);
    int ProcessCommand();

  public:
    UICommunication() {};

    /*
     * Run as the main method of communication with the UI.
     *
     * @return 0 if the loop ends ok, an error code otherwise
     */
    int MainLoop();
};
