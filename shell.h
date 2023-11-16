#ifndef SHELL_H
#define SHELL_H
/*
 *The kjxjhcjxh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <stdarg.h>

#define MAX_ARGS 128
/*
 *thebse aibfbskf
 */
void display_prompt(void);
void hsh_print(const char *message);
void read_command(char *command, size_t size);
void execute_command(const char *command);
void parse_args(const char *command, char *args[]);
char *find_command_in_path(const char *command);
void exit_shell(void);
void env_shell(void);

#endif /* SHELL_H */