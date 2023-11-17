#include "shell.h"
/**
 * ensures that the parent( the shell)
 * waits fot the child before continuing
 * execution
*/

void wait_for_child(pid_t child_pid)
{
int status;

if (waitpid(child_pid, &status, 0) == -1)
{
perror("waitpid");
exit(EXIT_FAILURE);
}
}

