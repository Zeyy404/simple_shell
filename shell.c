
#include "main.h"

/**
 * is_whitespace - Checks if a character is a whitespace character.
 * @c: character input
 * Return: 1 if it is, 0 otherwise.
 */
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * main - simple shell program
 * @argc: arguments counts
 * @argv: arguments vectors
 * Return: 0 (Success), 2 (Misuse of Shell Builtins),
 *              or 127 (Command Not Found)
 */
int main(int __attribute__((__unused__))argc, char *argv[])
{
	char *prompt = "($) ", *lineptr = NULL, *_argv = argv[0];
	size_t n = 0;
	ssize_t nchars_read = 0, j;
	int i, re = 0, is_space;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, strlen(prompt));
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
			break;
		is_space = 1;
		for (j = 0; j < nchars_read; j++)
		{
			if (!is_whitespace(lineptr[j]))
			{
				is_space = 0;
				break;
			}
		}
		if (is_space)
			continue;
		argv = readCommand(lineptr, argv);
		if (strcmp(argv[0], "exit") == 0)
			re = exitShell(_argv, argv, lineptr, re);
		else if (strcmp(argv[0], "cd") == 0)
			re = changeDirectory(_argv, argv);
		else if (strcmp(argv[0], "env") == 0)
			re = print_env();
		else
			re = executeCommand(_argv, argv);
		for (i = 0; argv[i] != NULL; i++)
			free(argv[i]);
		free(argv);
	}
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(lineptr);
	return (re);
}
