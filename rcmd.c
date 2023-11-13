#include "main.h"

/**
 * readCommand - Parses the input in the CLI
 * @lineptr: input in the CLI
 * @argv: a pointer to array of strings
 * Return: argv
 */
char **readCommand(char *lineptr, char *argv[])
{
	char *lineptr_copy = NULL, *token;
	const char *delimeter = " \n\t";
	int i, n_token = 0;

	lineptr_copy = strdup(lineptr);
	token = strtok(lineptr_copy, delimeter);
	while (token != NULL)
	{
		n_token++;
		token = strtok(NULL, delimeter);
	}
	argv = malloc(sizeof(char *) * (n_token + 1));
	if (argv == NULL)
	{
		free(lineptr_copy);
		return (NULL);
	}
	token = strtok(lineptr, delimeter);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(argv[i], token);
		token = strtok(NULL, delimeter);
	}
	argv[i] = NULL;
	free(lineptr_copy);
	return (argv);
}
