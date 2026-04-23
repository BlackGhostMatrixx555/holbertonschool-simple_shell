#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: the string to measure
 *
 * Return: length of s, or 0 if s is NULL
 */
int _strlen(const char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strdup - Duplicates a string into a new allocated buffer
 * @s: the string to duplicate
 *
 * Return: pointer to the new string, or NULL on failure or if s is NULL
 */
char *_strdup(const char *s)
{
	char *copy = NULL;
	int len = 0;
	int i = 0;

	if (s == NULL)
		return (NULL);

	len = _strlen(s);
	copy = malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);

	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';

	return (copy);
}

/**
 * _getenv - Retrieves a variable's value from the environment
 * @name: the variable name to search for (without '=')
 *
 * Return: pointer to the value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = 0;

	if (name == NULL)
		return (NULL);

	len = _strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0
			&& environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}

	return (NULL);
}
