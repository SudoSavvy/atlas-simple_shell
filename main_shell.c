#include "shell.h"

/**
 * main - Entry point for the shell.
 *
 * Return: 0 on success, otherwise an error code.
 */
int main(void)
{
    char *line = NULL; /* Pointer to store the input line */
    size_t len = 0; /* Variable to store the size of the input line */
    ssize_t nread; /* Variable to store the number of characters read */
    char *token; /* Pointer to store each token from the input line */
    char *argv[100]; /* Array to store the arguments */

    while (1)
    {
        printf(PROMPT); /* Print the prompt */
        nread = getline(&line, &len, stdin); /* Read the input line */
        if (nread == -1) /* Check for end of input */
        {
            free(line); /* Free the allocated memory for the input line */
            printf("\n"); /* Print a new line */
            break; /* Exit the loop */
        }

        int i = 0; /* Initialize the argument index */
        token = strtok(line, " \n"); /* Tokenize the input line */
        while (token != NULL) /* Loop through each token */
        {
            argv[i++] = token; /* Store the token in the argument array */
            token = strtok(NULL, " \n"); /* Get the next token */
        }
        argv[i] = NULL; /* Null-terminate the argument array */

        if (argv[0] == NULL) /* Check if no command was entered */
            continue; /* Skip to the next iteration of the loop */

        handle_exit(argv, line); /* Handle the exit command */
        handle_cd(argv); /* Handle the cd command */
        execute_command(argv); /* Execute the entered command */
    }

    free(line); /* Free the allocated memory for the input line */
    return (0); /* Return success */
}
