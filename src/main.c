#include "board.h"
#include "ui_communication.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	int ret;
	struct board *b;

	b = get_new_board();
	board_print(b);

	ret = main_loop();
	if (ret) {
		fprintf(stderr, "main_loop exit with error code: %d\n", ret);
		exit(ret);
	}

	return 0;
}
