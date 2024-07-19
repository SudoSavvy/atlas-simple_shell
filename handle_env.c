#include "shell.h"

/**
 * handle_env - Handles the env built-in command
 * @argv: The argument vector
 */

void handle_env(char **argv)
{
    int i;

    if (strcmp(argv[0], "env") == 0)
    {
        for (i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
    }
}
