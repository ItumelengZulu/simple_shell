#include "shell.h"

void execute_command(const char *command) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        /* Child process */

        /* Parse the command and its arguments */
        char *args[128]; /* Maximum 128 arguments (adjust as needed) */
        int arg_count = 0;

        char *token = strtok((char *)command, " ");
        while (token != NULL && arg_count < 127) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; /* Null-terminate the arguments array */

        /* Execute the command */
        execvp(args[0], args);

        /* If execvp fails, print an error message */
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        int status;
        if (waitpid(child_pid, &status, 0) == -1) {
            perror("Error waiting for child process");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                fprintf(stderr, "Command exited with status %d\n", exit_status);
            }
        } else if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            fprintf(stderr, "Command terminated by signal %d\n", signal_number);
        }
    }
}
