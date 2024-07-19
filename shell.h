#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROMPT "$ "

void execute_command(char **argv);
void handle_exit(char **argv, char *line);
void handle_env(char **argv);

#endif /* SHELL_H */
