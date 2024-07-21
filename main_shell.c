#include "shell.h"

/**
 * main - Entry point for the shell.
 * 
 * Return: 0 on success, otherwise an error code.
 */
int main(void)
{
    char *line = NULL; /* Pointer to hold the input line */
    size_t len = 0; /* Size of the buffer for getline */
    ssize_t nread; /* Number of characters read by getline */
    char *token; /* Token pointer for strtok */
    char *argv[100]; /* Argument vector to hold the command and its arguments */

    while (1) /* Infinite loop for the shell prompt */
    {
        printf(PROMPT); /* Print the prompt */
        
        /* Read the input line */
        nread = getline(&line, &len, stdin);
        if (nread == -1) /* Check for end of file (Ctrl+D) */
        {
            free(line); /* Free the allocated memory for line */
            printf("\n");
            break; /* Exit the loop */
        }

        int i = 0; /* Index for the argument vector */
        
        /* Tokenize the input line */
        token = strtok(line, " \n");
        while (token != NULL) /* Iterate through each token */
        {
            argv[i++] = token; /* Store the token in argv */
            token = strtok(NULL, " \n"); /* Get the next token */
        }
        argv[i] = NULL; /* Null-terminate the argument vector */

        if (argv[0] == NULL) /* Check if no command was entered */
            continue; /* Continue to the next iteration of the loop */

        handle_exit(argv, line); /* Handle the exit built-in command */
        handle_print_hello(argv); /* Handle the custom built-in command */

        execute_command(argv); /* Execute the entered command */
    }

    free(line); /* Free the allocated memory for line */
    return (0); /* Return success */
}
