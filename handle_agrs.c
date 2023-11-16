#include "shell.h"

/**
 * this segment of the code is meant to handle arguments
*/

void parse_args(const char *command, char *args[]) {
    int arg_count = 0;

    char *token = strtok((char *)command, " ");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL; /* Null-terminate the arguments array */
}