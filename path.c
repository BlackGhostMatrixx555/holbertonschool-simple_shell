#include "shell.h"

/**
 * get_path_env - Retrieves the value of the PATH environment variable
 *
 * Return: pointer to the PATH value string, or NULL if not found
 */
static char *get_path_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

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

	path_env = get_path_env();
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(cmd) + 2;
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
