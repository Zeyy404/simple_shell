#include "main.h"

/**
 * getCommand - gets the path of the command from the PATH global variable
 * @command: a pointer to the input command
 * Return: a pointer to the path or NULL
 */
char *getCommand(char *command)
{
	char *path = NULL, *path_copy = NULL, *path_token = NULL, *file_path = NULL;
	int len_command, len_dir;
	struct stat buffer;

	path = getenv("PATH");
	if (path == NULL && strncmp(command, "/", 1) == 0)
		path = strdup(command);
	if (path)
	{
		path_copy = strdup(path);
		len_command = strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			len_dir = strlen(path_token);
			file_path = malloc(len_command + len_dir + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				if (strcmp(path, command) == 0)
					free(path);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (strcmp(path, command) == 0)
			free(path);
		if (stat(command, &buffer) == 0)
			return (command);
	}
	return (NULL);
}
