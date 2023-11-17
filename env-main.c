#include "shell.h"

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
