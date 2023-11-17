#include "shell.h"
/**
 * this function controls the main funtions of the env
 * dislay, read, execute command etc
 * it also frees the memory allocated for input
 * keeps program in a loop for new commands
*/

int main(void)
{
char *input;

while (1)
{
display_prompt();
input = read_command();
if (input == NULL)
{
free(input);
break;
}

if (*input)
execute_command(input);

free(input);
}

return (0);
}
