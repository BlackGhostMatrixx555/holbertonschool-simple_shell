#include "shell.h"

/**
 * process_line - Parses and executes one input line
 * @line: the raw input string read from stdin
 * @argv0: shell name for error messages
 * @last_status: pointer to the last exit status to update
 *
 * Return: 1 if shell should exit, 0 otherwise
 */
static int process_line(char *line, char *argv0, int *last_status)
{
	char **args = NULL;
	int builtin_ret = 0;

	if (line[0] == '\0' || line[0] == '\n')
		return (0);

	args = split_line(line);
	if (args == NULL || args[0] == NULL)
	{
		free_args(args);
		return (0);
	}

	builtin_ret = handle_builtins(args);
	if (builtin_ret == 2)
	{
		free_args(args);
		return (1);
	}
	if (!builtin_ret)
		*last_status = execute_command(args, argv0);

	free_args(args);
	return (0);
}

/**
 * main - Entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] used for error messages
 * @env: environment variables (unused, using extern environ)
 *
 * Return: last command exit status
 */
int main(int argc __attribute__((unused)),
	char **argv,
	char **env __attribute__((unused)))
{
	char *line = NULL;
	int last_status = 0;

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

		if (process_line(line, argv[0], &last_status))
		{
			free(line);
			return (last_status);
		}

		free(line);
	}

	return (last_status);
}
