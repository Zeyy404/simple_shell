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
	char *gcmd;
	int status, exit_status;

	gcmd = getCommand(argv[0]);
	if (gcmd != NULL)
	{
		child = fork();
		if (child == -1)
			return (1);
		if (child == 0)
		{
			if (execve(gcmd, argv, environ) == -1)
			{
				fprintf(stderr, "%s: 1: %s: Permission denied\n", _argv, argv[0]);
				exit(126);
			}
		}
		else
		{
			wait(&status);
			if (strcmp(gcmd, argv[0]) != 0)
				free(gcmd);
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				return (exit_status);
		}
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", _argv, argv[0]);
		return (127);
	}
	return (0);
}
