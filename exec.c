#include "shell.h"
/**
 * This function is responsible for creating a child process
 * using the fork system call 
 * then replacing the child process 
 * with a new program using the execlp system call
*/

void execute_command(char *command)
{
pid_t child_pid;

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (child_pid == 0)
{
/* Child process */
if (execlp(command, command, (char *)NULL) == -1)
{
perror("execlp");
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process */
wait_for_child(child_pid);
}
}
