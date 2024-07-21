#include "shell.h"

/**
 * handle_exit - Handles the exit built-in command
 * @argv: The argument vector
 * @line: The input line to free
 */
void handle_exit(char **argv, char *line)
{
    if (strcmp(argv[0], "exit") == 0)
    {
        free(line);
        exit(0);
    }
}
