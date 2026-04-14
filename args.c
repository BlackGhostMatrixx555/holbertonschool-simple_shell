#include "shell.h"

/**
 * split_line - Splits a line into an array of tokens
 * @line: the input string to tokenize
 *
 * Splits on spaces and tabs. Returns a NULL-terminated
 * array of pointers into a duplicated copy of the line.
 *
 * Return: NULL-terminated array of strings, or NULL on failure
 */
char **split_line(char *line)
{
	char **args = NULL;
	char *token = NULL;
	char *line_copy = NULL;
	int count = 0;
	int i = 0;

	line_copy = strdup(line);
	if (line_copy == NULL)
		return (NULL);

	token = strtok(line_copy, " \t");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	free(line_copy);

	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	return (args);
}

/**
 * free_args - Frees an array of argument strings
 * @args: the NULL-terminated array to free
 *
 * Note: does not free the strings themselves since they
 * point into the original line buffer.
 *
 * Return: void
 */
void free_args(char **args)
{
	if (args != NULL)
		free(args);
}
