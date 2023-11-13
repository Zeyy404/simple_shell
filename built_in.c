#include "main.h"

/**
 * exitShell - exits the shell
 * @_argv: a pointer to the program (Shell) name
 * @argv: a pointer to array of strings
 * @lineptr: a pointer to the input on the CLI
 * @re: return value
 * Return: void
 */
void exitShell(char *_argv, char *argv[], char *lineptr, int re)
{
	char *endptr;
	long exitStatus;
	int i;

	free(lineptr);
	if (argv[1] != NULL)
	{
		exitStatus = strtol(argv[1], &endptr, 10);
		if (*endptr == '\0' || *endptr == '\n')
		{
			for (i = 0; argv[i] != NULL; i++)
				free(argv[i]);
			free(argv);
			if (exitStatus >= 0 && exitStatus <= 255)
			{
				exit((int)exitStatus);
			}
			else
			{
				fprintf(stderr, "%s: 1: %s: Illegal number: %s\n", _argv, argv[0], argv[1]);
			}
		}
		else
		{
			fprintf(stderr, "%s: 1: %s: Illegal number: %s\n", _argv, argv[0], argv[1]);
		}
	}
	else
	{
		for (i = 0; argv[i] != NULL; i++)
			free(argv[i]);
		free(argv);
		exit(re);
	}
}

/**
 * changeDirectory - changes directories within the program (Shell) session
 * @_argv: a pointer to the program (Shell) name
 * @argv: a pointer to array of string
 * Return: 0 (Success), or 2 (Misuse of Shell Builtins)
 */
int changeDirectory(char *_argv, char *argv[])
{
	char *home_dir = NULL, *prev_dir = NULL;
	char *buf = getcwd(NULL, 0);

	home_dir = getenv("HOME");
	if (argv[1] == NULL)
	{
		if (chdir(home_dir) != 0)
		{
			free(buf);
			return (2);
		}
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		prev_dir = getenv("OLDPWD");
		if (prev_dir == NULL)
		{
			printf("%s\n", buf);
		}
		else
		{
			chdir(prev_dir);
			printf("%s\n", prev_dir);
		}
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			fprintf(stderr, "%s: 1: cd: can't cd to %s\n", _argv, argv[1]);
			free(buf);
			return (2);
		}
	}
	if (buf != NULL)
	{
		setenv("OLDPWD", buf, 1);
	}
	free(buf);
	return (0);
}
