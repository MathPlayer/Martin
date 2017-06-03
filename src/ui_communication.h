#pragma once

/** Defined modes of interaction with an UI. */
#define UI_MODE_UCI     "uci"
#define UI_MODE_XBOARD  "xboard"

/**
 * Run as the main method of communication with the UI.
 *
 * @return 0 if the loop ends ok, an error code otherwise
 */
int main_loop();
