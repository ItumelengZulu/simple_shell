#ifndef SHELL_H
#define SHELL_H
/**
 * no comment
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
#define MAX_BUFFER_SIZE 1024
#define MAX_COMMANDS 128

typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;
/**
 *h file 
 */
void display_prompt(void);
void hsh_print(const char *message);
void read_command(char *command, size_t size);
void execute_command(const char *command);
void parse_args(const char *command, char *args[]);
char *find_command_in_path(const char *command);
void exit_shell(void);
void env_shell(void);
char *custom_getline(void);
void free_list(list_t *head);
list_t *add_node_end(list_t **head, const char *str);
void setenv_builtin(char **args);
void unsetenv_builtin(char **args);
void cd_builtin(char **args);

#endif /* SHELL_H */