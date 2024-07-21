#include "shell.h"

/**
 * execute_command - Executes a command
 * @argv: The argument vector
 */
void execute_command(char **argv)
{
    pid_t pid;

    pid = fork(); /* Create a new process */
    if (pid == -1) /* Check if fork failed */
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) /* Child process */
    {
        if (execve(argv[0], argv, environ) == -1) /* Try to execute the command */
        {
            perror("execve");
            exit(EXIT_FAILURE); /* Exit if execve fails */
        }
    }
    else /* Parent process */
    {
        int status;

        waitpid(pid, &status, 0); /* Wait for the child process to finish */
    }
}
