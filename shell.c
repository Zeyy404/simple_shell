#include "main.h"

/**
 * main - simple shell program
 * @ac: arguments counts
 * @av: arguments vectors
 * Return: 0 (Success), 2 (Misuse of Shell Builtins),
 *              or 127 (Command Not Found)
 */
int main(int __attribute__((__unused__))ac, char *av[])
{
	char *prompt = "($) ", *lineptr = NULL, *_argv = av[0];
	size_t n = 0;
	ssize_t nchars_read = 0, j;
	int re = 0, is_space;

	while (nchars_read != -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, strlen(prompt));
		nchars_read = getline(&lineptr, &n, stdin);
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
		av = readCommand(lineptr, av);
		if (strcmp(av[0], "exit") == 0)
			re = exitShell(_argv, av, lineptr, re);
		else if (strcmp(av[0], "cd") == 0)
			re = changeDirectory(_argv, av);
		else if (strcmp(av[0], "env") == 0)
			re = print_env();
		else if (strcmp(av[0], "setenv") == 0 && av[1] != NULL && av[2] != NULL)
			re = set_env(_argv, av);
		else if (strcmp(av[0], "unsetenv") == 0)
			re = unset_env(_argv, av);
		else
			re = executeCommand(_argv, av);
		free_memory(av);
	}
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(lineptr);
	return (re);
}

/**
 * free_memory - frees the memory allocated for argv
 * @argv: a pointer to array of strings
 * Return: void
 */
void free_memory(char *argv[])
{
	int i;

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}
