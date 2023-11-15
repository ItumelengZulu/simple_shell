#include "hsh.h"

/**
 * this is my second try at this, 
 * i undertand shell a little better
 * need to implement a local checker
 * 
*/
int main() {
    char command[MAX_COMMAND_LENGTH];
    
    /* Main shell loop */
    while (1) {
        display_prompt();

        /* Read a command from the user */
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            /* Handle end-of-file (Ctrl+D) */
            printf("\n");
            break;
        }

         /* Remove the newline character at the end */
        command[strcspn(command, "\n")] = '\0';

        /* Execute the command */
        execute_command(command);
    }

    printf("Exiting shell.\n");
    return 0;
}

/**
 * display_prompt - Display a simple shell prompt
 */
void display_prompt() {
    printf("$ "); /* Display a simple prompt */
}

/**
 * execute_command - Execute a command in a child process
 * @command: The command to execute
 */
void execute_command(char *command) {
    /* Fork a new process */
    pid_t pid = fork();

    if (pid == -1) {
        /* Forking error */
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
         /* Child process */
        execlp(command, command, (char *)NULL);

        /* If execlp fails, print an error message */
        perror("Error");
        exit(EXIT_FAILURE);
    } else {
       /* Parent process */
        int status;
        waitpid(pid, &status, 0);

       /* Check if the child process exited normally */
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }
}
