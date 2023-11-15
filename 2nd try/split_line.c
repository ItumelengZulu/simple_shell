#include "shell.h"

/**
 * split_line - split a string into multiple strings
 * @line: string to be split
 *
 * Return: pointer that points to the new array
 */
char **split_line(char *line)
{
    int bufsize = 64;
    int i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "allocation error in split_line: tokens\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        /* handle comments */
        if (token[0] == '#')
        {
            break;
        }

        tokens[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (!tokens[i])
        {
            fprintf(stderr, "allocation error in split_line: token\n");
            exit(EXIT_FAILURE);
        }

        strcpy(tokens[i], token);
        i++;

        if (i >= bufsize)
        {
            bufsize += bufsize;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "reallocation error in split_line: tokens");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }

    tokens[i] = NULL;
    return tokens;
}
