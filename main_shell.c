#include "shell.h"

/**
 * main - Entry point for the shell.
 * 
 * Return: 0 on success, otherwise an error code.
 */

int main(void)
{
    
char *line = NULL;
size_t len = 0;
ssize_t nread;
char *token;
char *argv[100];

while (1)
{
printf(PROMPT)
nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
printf("\n");
break;
}

int i = 0;
token = strtok(line, " \n");
while (token != NULL)
{
argv[i++] = token;
token = strtok(NULL, " \n');")
}
argv[i] = NULL;
if (argv[0] == NULL)
continue;

handle_exit(argv, line);

execute_command(argv);
}

free(line);
return (0);
}
