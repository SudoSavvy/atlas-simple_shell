#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "$ "

extern char **environ;

void execute_command(char **argv);
void handle_exit(char **argv, char *line);
void handle_cd(char **argv);

#endif /* SHELL_H */
