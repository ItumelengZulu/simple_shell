// execute.c

#include "shell.h"

/**
 * execute_command - Execute a shell command.
 * @command: The command to execute.
 */
void execute_command(const char *command)
{
    char *commands[MAX_COMMANDS]; // Maximum 128 commands (adjust as needed)
    int command_count = 0;

    char *token = strtok((char *)command, ";");
    while (token != NULL)
    {
        commands[command_count++] = token;
        token = strtok(NULL, ";");
    }

   
    for (int i = 0; i < command_count; ++i)
    {
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0)
        {
            /* Child process */

            
            char *args[MAX_ARGS]; /* Maximum 128 arguments (adjust as needed) */
            int arg_count = 0;

            size_t j = 0;
            size_t start = 0;

            
            while (commands[i][j] != '\0')
            {
                
                while (commands[i][j] == ' ' || commands[i][j] == '\t' || commands[i][j] == '\n')
                {
                    j++;
                }

                
                start = j;

               
                while (commands[i][j] != ' ' && commands[i][j] != '\t' && commands[i][j] != '\n' && commands[i][j] != '\0')
                {
                    j++;
                }

               
                if (j > start)
                {
                    args[arg_count] = strndup(commands[i] + start, j - start);
                    arg_count++;

                    
                    if (arg_count >= MAX_ARGS - 1)
                    {
                        fprintf(stderr, "Too many arguments. Maximum allowed: %d\n", MAX_ARGS - 1);
                        exit(EXIT_FAILURE);
                    }
                }
            }

            args[arg_count] = NULL; /* Null-terminate the arguments array */

            
            execvp(args[0], args);

            
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            int status;
            if (waitpid(child_pid, &status, 0) == -1)
            {
                perror("Error waiting for child process");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0)
                {
                    fprintf(stderr, "Command exited with status %d\n", exit_status);
                }
            }
            else if (WIFSIGNALED(status))
            {
                int signal_number = WTERMSIG(status);
                fprintf(stderr, "Command terminated by signal %d\n", signal_number);
            }
        }
    }
}

