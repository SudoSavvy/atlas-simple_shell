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
        printf(PROMPT); /* Display the prompt to the user */
        
        nread = getline(&line, &len, stdin); /* Read a line of input from the user */
        if (nread == -1) /* Check for end-of-file (Ctrl+D) or error */
        {
            free(line); /* Free the allocated memory for the line */
            printf("\n"); /* Print a newline for formatting */
            break; /* Exit the loop to terminate the shell */
        }

        int i = 0;
        token = strtok(line, " \n"); /* Split the line into tokens using space and newline as delimiters */
        while (token != NULL) /* Continue until all tokens are processed */
        {
            argv[i++] = token; /* Store each token in the argv array */
            token = strtok(NULL, " \n"); /* Get the next token */
        }
        argv[i] = NULL; /* Null-terminate the argv array */

        if (argv[0] == NULL) /* If no command is entered, continue to the next iteration */
            continue;

        if (strcmp(argv[0], "exit") == 0) /* If the command is "exit" */
            handle_exit(argv, line); /* Call the exit handler */

        execute_command(argv); /* Execute the entered command */
    }

    free(line); /* Free the allocated memory for the line before exiting */
    return (0); /* Return 0 to indicate successful execution */
}
