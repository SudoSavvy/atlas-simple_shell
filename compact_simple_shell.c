#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void print_env(void);
void handle_exit(void);
void say_hello(void);
void print_date(void);
void print_help(void);
int process_command(const char *cmd);

/* Command handler functions */
void print_env(void)
{
    char *env = getenv("PATH");
    if (env)
    {
        printf("PATH=%s\n", env);
    }
    else
    {
        printf("PATH environment variable not set.\n");
    }
}

void handle_exit(void)
{
    printf("Exiting...\n");
    exit(0);
}

void say_hello(void)
{
    printf("Hello, world!\n");
}

void print_date(void)
{
    time_t now = time(NULL);
    if (now != -1)
    {
        printf("Current date and time: %s", ctime(&now));
    }
    else
    {
        perror("time");
    }
}

void print_help(void)
{
    printf("Available commands:\n");
    printf("  exit    - Exit the shell\n");
    printf("  env     - Print the PATH environment variable\n");
    printf("  hello   - Print a greeting message\n");
    printf("  date    - Print the current date and time\n");
    printf("  help    - Show this help message\n");
}

/* Command table */
typedef void (*command_handler)(void);

typedef struct {
    const char *command;
    command_handler handler;
} command_entry;

command_entry commands[] = {
    {"exit", handle_exit},
    {"env", print_env},
    {"hello", say_hello},
    {"date", print_date},
    {"help", print_help},  /*dded help command*/
    /*Add more commands here*/
};

#define NUM_COMMANDS (sizeof(commands) / sizeof(command_entry))

/* Process commands */
int process_command(const char *cmd)
{
    size_t i;
    for (i = 0; i < NUM_COMMANDS; i++)
    {
       if (strcmp(cmd, commands[i].command) == 0)
        {
            commands[i].handler();
            return 1;  /*Command processed*/
        }
    }
    return 0;  /*Command not processed*/
}

/* Main loop of the shell */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        printf("simple_shell> ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (fgets(stdin))
            {
                printf("\n");
                break;  /*Exit on EOF*/
            }
            else
            {
                perror("getline");
                continue;
            }
        }

        line[strcspn(line, "\n")] = 0;  /*Remove trailing newline*/

        if (strlen(line) == 0)
        {
            continue;  /*Skip empty input*/
        }

        if (!process_command(line))
        {
            fprintf(stderr, "%s: command not found\n", line);
        }
    }

    free(line);
    return 0;
}
