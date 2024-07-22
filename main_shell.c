#include "shell.h"

/**
 * main - Entry point for the shell.
 * 
 * Return: 0 on success, otherwise an error code.
 */
int main(void)
{
    char *line = NULL; /* Pointer to store the input line */
    size_t len = 0; /* Variable to store the length of the line */
    ssize_t nread; /* Variable to store the number of characters read */
    char *token; /* Pointer to store each token */
    char *argv[100]; /* Array to store arguments */

    while (1)
    {
        printf(PROMPT); /* Display the prompt */
        nread = getline(&line, &len, stdin); /* Read a line from standard input */
        if (nread == -1) /* Check for end of input or error */
        {
            free(line); /* Free the line buffer */
            printf("\n"); /* Print a new line */
            break; /* Exit the loop */
        }

        int i = 0; /* Initialize the argument index */
        token = strtok(line, " \n"); /* Tokenize the input line */
        while (token != NULL) /* Loop through all tokens */
        {
            argv[i++] = token; /* Store the token in argv */
            token = strtok(NULL, " \n"); /* Get the next token */
        }
        argv[i] = NULL; /* Null-terminate the argument list */
        
        if (argv[0] == NULL) /* Check for empty input */
            continue; /* Continue to the next iteration */

        handle_exit(argv, line); /* Handle the exit command */
        handle_cd(argv); /* Handle the cd command */
        execute_command(argv); /* Execute the entered command */
    }

    free(line); /* Free the line buffer */
    return (0); /* Return success */
}
