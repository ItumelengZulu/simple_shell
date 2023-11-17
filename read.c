#include "shell.h"
/**
 * this read function uses getline to read
 * user input from the shell
 * it gets the information line by line hence
 * getline
*/

char *read_command(void)
{
char *buffer = NULL;
size_t bufsize = 0;

if (getline(&buffer, &bufsize, stdin) == EOF)
return (NULL);

return (buffer);
}

