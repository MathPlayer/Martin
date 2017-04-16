#pragma once

#include <string>

/** Defined modes of interaction with an UI. */
#define UI_MODE_UCI     "uci"
#define UI_MODE_XBOARD  "xboard"

/**
 * Start communication with the UI.
 *
 * @return 0 if everything is ok, an error code otherwise
 */
int initCommunication();
