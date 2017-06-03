#include "ui_communication.h"
#include "common.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

const char * const xboard_features[] = {
#ifdef DEBUG
	"feature debug=1",                  /* show debug messages */
#endif
	"feature sigint=0",                 /* do not use SIGINT */
	"feature myname=\""ENGINE_NAME"\"", /* engine name */
	"feature san=0",                    /* use coordinate notation */
	"feature variants=\"normal\"",      /* play only standard chess */
	"feature ping=0",                   /* do not use ping */
	"feature analyze=0",                /* do not use analyze */
	"feature done=1"                    /* end of features */
};

static char command_buffer[50];
static int read_command() {
	int i;
	memset(command_buffer, 0, 50 * sizeof(char));
	for (i = 0; i < 50 && (command_buffer[i] = getchar()) != '\n'; i++);
	command_buffer[i] = 0;
#ifdef DEBUG
	printf("# received command: '%s'\n", command_buffer);
#endif
	return i;
}

static void write_command(const char *command)
{
	printf("%s\n", command);
	fflush(stdout);
}

static int negociate_xboard_features()
{
	const int N = sizeof(xboard_features) / sizeof(xboard_features[0]);
	for (int i = 0; i < N; i++) {
		write_command(xboard_features[i]);
		read_command();
		if (!strcmp(command_buffer, "rejected")) {
			fprintf(stderr, "Error: rejected command '%s'.\n",
					xboard_features[i]);
			return EINVAL;
		} else if (strcmp(command_buffer, "accepted")) {
			fprintf(stderr, "Error: not accepted command '%s'.\n",
					xboard_features[i]);
			return EINVAL;
		}
	}
	return 0;
}

int main_loop()
{
	int exit_loop = 0;

	while (!exit_loop) {
		read_command();
		if (!strcmp(command_buffer, "quit")) {
			return 0;
		} else if (!strcmp(command_buffer, "xboard")) {
			exit_loop = negociate_xboard_features();
			if (exit_loop) {
				fprintf(stderr, "Xboard negociation failed\n");
			}
		} else {
			return EINVAL;
		}
	}
	return exit_loop;
}
