#include "shell.h"

/**
 * cd_builtin - Change the current directory of the process.
 * @args: An array of arguments, where args[1] is the directory to change to.
 */
void cd_builtin(char **args) {
char *new_dir;
char *current_dir;

/* If no argument is given, interpret it like cd $HOME */
if (args[1] == NULL || _strcmp(args[1], "~") == 0)
{
    new_dir = _getenv("HOME");
}
else if (_strcmp(args[1], "-") == 0)
{
/* If the argument is "-", change to the previous directory */
    new_dir = _getenv("OLDPWD");
}
else
{
    new_dir = args[1];
}

/* Update the environment variable PWD */
if ((current_dir = getcwd(NULL, 0)) == NULL)
{
    perror("Error getting current directory");
    exit(EXIT_FAILURE);
}

if (_setenv("OLDPWD", current_dir, 1) != 0)
{
    perror("Error setting environment variable OLDPWD");
    exit(EXIT_FAILURE);
}

free(current_dir);

if (chdir(new_dir) != 0)
{
    perror("Error changing directory");
    exit(EXIT_FAILURE);
}

/* Update the environment variable PWD after changing directory */
if ((current_dir = getcwd(NULL, 0)) == NULL)
{
    perror("Error getting current directory");
    exit(EXIT_FAILURE);
}

if (_setenv("PWD", current_dir, 1) != 0)
{
    perror("Error setting environment variable PWD");
    exit(EXIT_FAILURE);
}

    free(current_dir);
}
