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
    

    while (1) {
	int argc;
	/*char *token; */
    char ** env;

        display_prompt();

        /* Read a command from the user
	 * diff between shell and kernal */
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            /* Handle end-of-file (Ctrl+D) 
	     * to return the end of file use getc()  fgets()
	     * */
            printf("\n");
            break;
        }

        /* Remove the newline character at the end using string compliment span */
        input[strcspn(input, "\n")] = '\0';

	/* Tokenize the command line using strtok to get words from input
	 * assign it to the pointer of the token then iterate to check if
	 * there are more words in the token && argc
	 * token then added to args array in the argc index
	 * call strtok to check if the token has more words
	 * increament the argument count for the word
	 * */

	/*token = strtok(input, " "); */

   /*      argc = 0;
	 while (token != NULL && argc < MAX_ARGUMENTS - 1) {
	     args[argc++] = token;
    	    token = strtok(NULL, " ");
         }  */

	/* set last element of args array to Null for evecvp
	 * */
	/*args[argc] = NULL;*/
	argc = tokenize_input(input,args);

    /* this function tests for the built in "exit" command */
    if (strcmp(args[0], "exit") == 0) {
        printf("EXITing shell. \n");
        return 0;
    }

    /* this function  checks the command "env" and
    * prints the current enviroment */
    if (strcmp(args[0], "env") == 0) {
        for (env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
        continue;
    }

	/* check if the command exists in the specified path*/
	snprintf(command_path, sizeof(command_path),  "%s/%s", path, args[0]);


        /* Fork a new process has same data with parent and child however 
	 * different pid's hence parent and child still want to see how 
	 * multiple processes are added, nested if's mayba?
	 * */
	
	if (access(command_path, X_OK) ==0) {

   	   pid = fork();

        }if (pid == -1) {
            /* Forking error */
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process from the old replaced proccess  */
            execvp(args[0], args);

            /* If execvp fails, print an error message */
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
    return 0; /*line addded to indicate successful program termination */
    }


