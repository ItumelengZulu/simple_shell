#include "shell.h"

void hsh_print(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}


