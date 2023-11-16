#include "shell.h"

/**
 * env_shell - Print the current environment.
 */
void env_shell(void)
{
    char **env;
    extern char **environ;

    for (env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}
