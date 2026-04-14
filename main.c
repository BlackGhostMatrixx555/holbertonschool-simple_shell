#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] used for error messages
 * @env: environment variables (unused, using extern environ)
 *
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)),
	char **argv,
	char **env __attribute__((unused)))
{
	char *line = NULL;
	char **args = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue;
		}

		args = split_line(line);
		if (args == NULL || args[0] == NULL)
		{
			free(line);
			free_args(args);
			continue;
		}

		if (!handle_builtins(args))
			execute_command(args, argv[0]);

		free(line);
		free_args(args);
	}

	free(line);
	return (0);
}
