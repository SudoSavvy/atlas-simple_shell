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
        perror("fork"); /* Print error message */
        exit(EXIT_FAILURE); /* Exit with failure status */
    }
    if (pid == 0) /* Child process */
    {
        if (execve(argv[0], argv, environ) == -1) /* Execute command */
        {
            perror("execve"); /* Print error message */
            exit(EXIT_FAILURE); /* Exit with failure status */
        }
    }
    else /* Parent process */
    {
        int status;

        waitpid(pid, &status, 0); /* Wait for the child process to complete */
    }
}
