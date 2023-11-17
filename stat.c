#include "shell.h"

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
