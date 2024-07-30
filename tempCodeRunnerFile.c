/**
 * execute_command - Execute external commands.
 * @cmd: The command string input by the user.
 */
void execute_command(const char *cmd)
{
    char *args[100]; /* Array to hold command and arguments */
    char command[BUFFER_SIZE];
    char *token;
    int i = 0;

    snprintf(command, BUFFER_SIZE, "%s", cmd);

    /* Tokenize the command string */
    token = strtok(command, " ");
    while (token != NULL)
    {
        args[i++] = token; /* Store each token */
        token = strtok(NULL, " ");
    }
    args[i] = NULL; /* Null-terminate the argument list */

    if (!file_exists(args[0]))
    {
        fprintf(stderr, "Command not found or is not executable: %s\n", args[0]);
        return;
    }

    /* Cast args to const char * const * */
    execvp(args[0], (const char *const *)args);

    /* If execvp returns, an error occurred */
    perror("execvp");
}