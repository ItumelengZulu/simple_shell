#include "shell.h"

char *read_command(void)
{
char *buffer = NULL;
size_t bufsize = 0;

if (getline(&buffer, &bufsize, stdin) == EOF)
return (NULL);

return (buffer);
}

