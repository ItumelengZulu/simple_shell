#include "shell.h"
/**
 * this function handles the process status
 * checks the status of the last executed command
 * and returns its exit status
*/

static int status;

int get_last_command_status(void)
{
if (!WIFEXITED(status))
{
fprintf(stderr, "Error: Last command has not exited\n");
return (-1);
}
return (WEXITSTATUS(status));
}
