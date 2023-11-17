#include "shell.h"
/**
 * this function returns the ppid
 * which is the parent procces id
*/

pid_t get_parent_process_id(void)
{
return (getppid());
}

