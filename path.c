#include "shell.h"

/**
 * Search for a command in the directories listed in PATH.
 * If found, return the full path; otherwise, return NULL.
 */
char *find_command_in_path(const char *command)
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL)
    {
        char cmd_path[256];
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, command);

        if (access(cmd_path, X_OK) == 0)
        {
            /* Command found in the current directory in PATH */
            free(path_copy);
            return strdup(cmd_path);
        }

        dir = strtok(NULL, ":");
    }

    /* Command not found in PATH */
    free(path_copy);
    return NULL;
}

