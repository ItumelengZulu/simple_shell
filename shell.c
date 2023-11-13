#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * this is my first shell, it doesnt do much so far but i am hoping to 
 * add more cool features and also learn how to add, modify then write
 * that cool documentation on how it works and how it was built
 * i could write a book in betty ('*.*')
 * its to clean
 * */

#define MAX_COMMAND_LENGTH 120

void display_prompt() {
    printf("$ "); /* Display a simple prompt i know that dollar sign */
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    while (1) {
        display_prompt();

        /* Read a command from the user
	 * diff between shell and kernal */
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            /* Handle end-of-file (Ctrl+D) 
	     * to return the end of file use getc()  fgets()
	     * */
            printf("\n");
            break;
        }

        /* Remove the newline character at the end using string compliment span */
        command[strcspn(command, "\n")] = '\0';

        /* Fork a new process has same data with parent and child however 
	 * different pid's hence parent and child still want to see how 
	 * multiple processes are added, nested if's mayba?
	 * */

   	 pid = fork();

        if (pid == -1) {
            /* Forking error */
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process from the old replaced proccess  */
            execlp(command, command, (char *)NULL);

            /* If execlp fails, print an error message */
            perror("Error");
            exit(EXIT_FAILURE);
        } else {
            /* Parent process uses waitpid to wait for any child process
	     * to terminate, if so that is gets info on the termination status,
	     * also allow for more control over the child processes in the program  */
            int status;
            waitpid(pid, &status, 0);

            /* Check if the child process exited normally using WIFEexited macro to check
	     * exit status*/
            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else {
                printf("Child process terminated abnormally\n");
            }
        }
    }

    printf("Exiting shell.\n");
    return 0;
}

