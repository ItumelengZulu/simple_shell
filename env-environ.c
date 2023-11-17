#include "shell.h"
/**
* This function prints the env variables of the
* current process.
*/
void print_environment(void)
{
int i = 0;
while (environ[i] != NULL)
{
printf("%s\n", environ[i]);
i++;
}
}

