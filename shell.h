/**
 * this is my .h file which does all the linking
 * of my program function and variables
*/
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Accesses the environment variables
*/
extern char **environ; 

void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
char *trim_spaces(char *str);
pid_t create_child_process(void);
pid_t get_process_id(void);
pid_t get_parent_process_id(void);
int get_last_command_status(void);
void print_environment(void);
void wait_for_child(pid_t child_pid);

#endif /* SHELL_H */
