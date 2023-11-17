#include "shell.h"

pid_t create_child_process(void)
{
pid_t child_pid = fork();

if (child_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

return (child_pid);
}

