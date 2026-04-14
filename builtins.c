#include "shell.h"

/**
 * builtin_env - Prints all environment variables to stdout
 *
 * Iterates through the environ array and prints each
 * variable followed by a newline.
 *
 * Return: void
 */
void builtin_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_builtins - Checks and executes built-in commands
 * @args: null-terminated array of arguments, args[0] is the command
 *
 * Handles: exit, env
 *
 * Return: 1 if a built-in was matched and handled, 0 otherwise
 */
int handle_builtins(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		exit(EXIT_SUCCESS);

	if (strcmp(args[0], "env") == 0)
	{
		builtin_env();
		return (1);
	}

	return (0);
}
