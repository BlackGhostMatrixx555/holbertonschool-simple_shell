#include "shell.h"

/**
 * find_in_path - Searches for a command in PATH directories
 * @cmd: the command name to search for
 *
 * Iterates through each directory in the PATH environment variable,
 * building the full path and checking if the file is executable.
 *
 * Return: allocated string with the full path, or NULL if not found
 */
char *find_in_path(char *cmd)
{
	char *path_env = NULL;
	char *path_copy = NULL;
	char *dir = NULL;
	char *full_path = NULL;
	size_t len = 0;

	path_env = _getenv("PATH");
	if (path_env == NULL || path_env[0] == '\0')
		return (NULL);

	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = _strlen(dir) + _strlen(cmd) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
