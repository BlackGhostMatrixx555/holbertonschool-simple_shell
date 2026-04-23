#include "shell.h"

/**
 * free_args - Frees the array of argument pointers
 * @args: the NULL-terminated array of strings to free
 *
 * Note: does not free the strings themselves since they
 * point into the original line buffer managed by main.
 *
 * Return: void
 */
void free_args(char **args)
{
	if (args != NULL)
		free(args);
}

/**
 * free_path - Frees a resolved path only if it was allocated
 * @path: the path string to free
 * @original: the original args[0] pointer
 *
 * Only frees path if it differs from original, meaning it
 * was allocated by find_in_path and not pointing to args[0].
 *
 * Return: void
 */
void free_path(char *path, char *original)
{
	if (path != NULL && path != original)
		free(path);
}
