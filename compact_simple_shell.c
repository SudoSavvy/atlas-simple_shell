#include <stdio.h>     /* Include standard I/O functions */
#include <stdlib.h>    /* Include standard library functions */
#include <string.h>    /* Include string handling functions */
#include <time.h>      /* Include time functions */
#include <unistd.h>    /* Include POSIX functions */

/* Declaration of environ */
extern char **environ;

#define BUFFER_SIZE 1024   /* Define a buffer size constant for command input */

/* Function prototypes */
void print_env(void);
void handle_exit(void);
void say_hello(void);
void print_date(void);
void print_help(void);
int process_command(const char *cmd);
void execute_command(const char *cmd);
int file_exists(const char *path);

/**
 * print_env - Print all environment variables to the console.
 */
void print_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env); /* Print each environment variable */
        env++;
    }
}

/**
 * handle_exit - Handle the 'exit' command by printing a message and exiting.
 */
void handle_exit(void)
{
    printf("Exiting...\n"); /* Print exiting message */
    exit(0); /* Exit the program with status 0 */
}

/**
 * say_hello - Print a greeting message to the console.
 */
void say_hello(void)
{
    printf("Hello, world!\n"); /* Print greeting message */
}

/**
 * print_date - Print the current date and time to the console.
 */
void print_date(void)
{
    time_t now = time(NULL);

    if (now != -1)
    {
        printf("Current date and time: %s", ctime(&now)); /* Print current date and time */
    }
    else
    {
        perror("time"); /* Print error message if time retrieval failed */
    }
}

/**
 * print_help - Print the help message listing all available commands.
 */
void print_help(void)
{
    printf("Available commands:\n");
    printf("  exit    - Exit the shell\n");
    printf("  env     - Print the environment variables\n");
    printf("  hello   - Print a greeting message\n");
    printf("  date    - Print the current date and time\n");
    printf("  help    - Show this help message\n");
}

/* Define a function pointer type for command handlers */
typedef void (*command_handler)(void);

/**
 * struct command_entry - Structure to hold a command and its handler.
 * @command: The command string that the user will input.
 * @handler: A function pointer to the function that handles the command.
 *
 * Description: This structure maps a command string to its corresponding 
 * handler function. It is used to define a list of supported commands 
 * and their respective functions that execute the command's logic. The 
 * `command` member holds the string that represents the command 
 * (e.g., "exit", "env", "hello"), and the `handler` member is a pointer 
 * to the function that will be called when the command is executed.
 */
typedef struct command_entry
{
    const char *command;
    command_handler handler;
} command_entry;

/* Array of command entries */
command_entry commands[] = {
    {"exit", handle_exit},
    {"env", print_env},
    {"hello", say_hello},
    {"date", print_date},
    {"help", print_help},
    /* Add more commands here */
};

#define NUM_COMMANDS (sizeof(commands) / sizeof(command_entry)) /* Calculate the number of commands */

/**
 * process_command - Process built-in commands.
 * @cmd: The command string input by the user.
 *
 * Return: 1 if the command was processed, 0 otherwise.
 */
int process_command(const char *cmd)
{
    size_t i;

    for (i = 0; i < NUM_COMMANDS; i++)
    {
        if (strcmp(cmd, commands[i].command) == 0)
        {
            commands[i].handler(); /* Call the corresponding command handler */
            return (1); /* Command processed */
        }
    }
    return (0); /* Command not processed */
}

/**
 * file_exists - Check if a file exists.
 * @path: The path to the file.
 *
 * Return: 1 if the file exists, 0 otherwise.
 */
int file_exists(const char *path)
{
    return (access(path, F_OK) == 0);
}

/**
 * execute_command - Execute external commands.
 * @cmd: The command string input by the user.
 */
void execute_command(const char *cmd)
{
    pid_t pid;

    pid = fork();  /* Create a new process */
    if (pid == -1) /* Check if fork failed */
    {
        perror("fork");
        return;
    }
    else if (pid == 0) /* Child process */
    {
        execlp(cmd, cmd, (char *)NULL);  /* Replace the child process with the command */
        perror("execlp"); /* If execlp fails */
        exit(EXIT_FAILURE); /* Exit the child process with failure status */
    }
}

/**
 * main - Main loop of the shell.
 *
 * Return: 0 on success, 1 on error.
 */
int main(void)
{
    char *newline;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        printf("simple_shell> "); /* Print shell prompt */
        fflush(stdout); /* Flush output buffer */

        nread = getline(&line, &len, stdin); /* Read input line */
        
        if (nread == -1)
        {
             /* If getline returns -1, it indicates an error or EOF */
            perror("getline"); /* Print error message if getline failed */
            break; /* Exit the loop if there is an error or EOF */
        }

        newline = strchr(line, '\n'); /* Find newline character */
        if (newline)
        {
            *newline = '\0'; /* Replace newline character with null terminator */
        }

        if (strlen(line) == 0)
        {
            continue; /* Skip empty input */
        }

        if (!process_command(line)) /* Process built-in commands */
        {
            execute_command(line); /* Execute external command */
        }
    }

    free(line); /* Free the allocated buffer */
    return (0);
}
