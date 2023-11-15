#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

int is_whitespace(char c);
char **readCommand(char *lineptr, char *argv[]);
char *getCommand(char *command);
int executeCommand(char *_argv, char *argv[]);
int exitShell(char *_argv, char *argv[], char *lineptr, int re);
int changeDirectory(char *_argv, char *argv[]);
int print_env(void);

#endif
