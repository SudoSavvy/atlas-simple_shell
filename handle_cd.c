#include "shell.h"

/**
 * handle_cd - Handles the cd built-in command
 * @argv: The argument vector
 */
void handle_cd(char **argv)
{
    if (strcmp(argv[0], "cd") == 0)
    {
        if (argv[1] == NULL)
        {
            fprintf(stderr, "cd: expected argument to \"cd\"\n");
        }
        else if (chdir(argv[1]) != 0)
        {
            perror("cd");
        }
    }
}
