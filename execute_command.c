#include "shell.h"

/**
 * execute_command - Executes a command
 * @argv: The argument vector
 */
void execute_command(char **argv)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (execve(argv[0], argv, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}
