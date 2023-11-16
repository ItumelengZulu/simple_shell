#include "shell.h"

char *find_command(const char *command) {
    /* Get the PATH environment variable */
    char *path = getenv("PATH");
    if (path == NULL) {
        perror("Error getting PATH");
        exit(EXIT_FAILURE);
    }

    /* Tokenize the PATH variable */
    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("Error duplicating PATH");
        exit(EXIT_FAILURE);
    }

    /* Check each directory in PATH for the command */
    char *token = strtok(path_copy, ":");
    while (token != NULL) {
        /* Construct the full path to the command */
        char full_path[MAX_PATH];
        if (snprintf(full_path, sizeof(full_path), "%s/%s", token, command) < 0) {
            perror("Error constructing full path");
            free(path_copy);
            exit(EXIT_FAILURE);
        }

        /* Check if the command exists at the current path */
        if (access(full_path, X_OK) == 0) {
            char *result = strdup(full_path);
            free(path_copy);
            return result;
        }

        /* Move to the next directory in PATH */
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
