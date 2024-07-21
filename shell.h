#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "$ "

extern char **environ;

void execute_command(char **argv);
void handle_exit(char **argv, char *line);

#endif /* SHELL_H */
