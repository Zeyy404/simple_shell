#include "main.h"

/**
 * main - simple shell program
 * @argc: arguments counts
 * @argv: arguments vectors
 * Return: 0 (Success), 2 (Misuse of Shell Builtins),
 *              or 127 (Command Not Found)
 */
int main(int __attribute__((__unused__))argc, char *argv[])
{
	char *prompt = "($) ", *lineptr = NULL;
	char *_argv = argv[0];
	size_t n = 0;
	ssize_t nchars_read = 0;
	int i, re = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, strlen(prompt));
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
			break;
		argv = readCommand(lineptr, argv);
		if (strcmp(argv[0], "exit") == 0)
			exitShell(_argv, argv, lineptr);
		else if (strcmp(argv[0], "cd") == 0)
			re = changeDirectory(_argv, argv);
		else
			re = executeCommand(_argv, argv);
		for (i = 0; argv[i] != NULL; i++)
			free(argv[i]);
		free(argv);
	}
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n", 1);
	}
	free(lineptr);
	return (re);
}