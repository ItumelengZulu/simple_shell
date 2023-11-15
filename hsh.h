/**
 * THIS IS MY H FILE 
*/
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stddef.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt();
void execute_command(char *command);

#endif
