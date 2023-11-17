#include "shell.h"

pid_t get_parent_process_id(void)
{
return (getppid());
}

