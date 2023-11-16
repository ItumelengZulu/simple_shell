#ifndef SHELL_H
#define SHELL_H
/**
 *Get a local checker for all projects
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define MAX_ARGS 128
#define MAX_PATH 1024
/**
 * On the 3rd try its finally working
 */
void display_prompt(void);
void hsh_print(const char *message);
void read_command(char *command, size_t size);
void execute_command(const char *command);
char *find_command(const char *command);
void parse_args(const char *command, char *args[]); 

#endif /* SHELL_H */
