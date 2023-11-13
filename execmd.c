#include "main.h"

/**
 * executeCommand - executes the input command
 * @_argv: a pointer the program (shell) name
 * @argv: a pointer to array of strings
 * Return: 0 (Success), or 127 (Command Not Found)
 */
int executeCommand(char *_argv, char *argv[])
{
	pid_t child;
	char *gcmd = NULL;
	int status;

	gcmd = getCommand(argv[0]);
	if (gcmd != NULL)
	{
		child = fork();
		if (child == -1)
			return (-1);
		if (child == 0)
		{
			execve(gcmd, argv, environ);
		}
		else
		{
			wait(&status);
			if (strcmp(gcmd, argv[0]) != 0)
				free(gcmd);
		}
	}
	else
	{
		printf("%s: 1: %s: not found\n", _argv, argv[0]);
		return (127);
	}
	return (0);
}
