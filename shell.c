#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mygetline.h"
/*
 * this is my first shell, it doesnt do much so far but i am hoping to 
 * add more cool features and also learn how to add, modify then write
 * that cool documentation on how it works and how it was built
 * i could write a book in betty ('*.*')
 * its to clean
 * this is more challenging than i initially expected 
 * */

#define MAX_COMMAND_LENGTH 120
#define MAX_ARGUMENTS 12
#define MAX_PATH_LENGTH 120

extern char ** environ;
void display_prompt() {
    printf("$ "); /* Display a simple prompt i know that dollar sign */
}


int tokenize_input(char *input, char *args[]) {
    int argc = 0;

    while (*input != '\0' && argc < MAX_ARGUMENTS - 1) {
        while (*input == ' ' || *input == '\t' || *input == '\n') {
            *input++ = '\0';
        }

        args[argc++] = input;

        while (*input != '\0' && *input != ' ' && *input != '\t' && *input != '\n') {
            input++;
        }
    }

    args[argc] = NULL;
    return argc;
}

int main() {
    pid_t pid;
    char *args[MAX_ARGUMENTS];
    char input[MAX_COMMAND_LENGTH];
    char command_path[MAX_PATH_LENGTH];
    char *path = "/bin";
    char **env;
    int exit_status;
    

    while (1) {
        int argc =0;

        display_prompt();

        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        tokenize_input(input, args);

        /* Check for built-in commands */
        if (strcmp(args[0], "exit") == 0) {
            if (argc > 1) {
                exit_status = atoi(args[1]);
                printf("Exiting shell with status %d.\n", exit_status);
                return exit_status;
            } else {
                printf("Exiting shell.\n");
                return 0;
            }
        } else if (strcmp(args[0], "env") == 0) {
            for (env = environ; *env != NULL; env++) {
                printf("%s\n", *env);
            }
            continue;
        }

        /* Check if the command exists in the specified path */
        snprintf(command_path, sizeof(command_path), "%s/%s", path, args[0]);

        /* Fork a new process */
        if (access(command_path, X_OK) == 0) {
            pid = fork();

            if (pid == -1) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                execvp(args[0], args);
                perror("Error");
                exit(EXIT_FAILURE);
            } else {
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    printf("Child process exited with status %d\n", WEXITSTATUS(status));
                } else {
                    printf("Child process terminated abnormally\n");
                }
            }
        }
    }

    printf("Exiting shell.\n");
    return 0;
}