#include "shell.h"

/**
 * display_prompt - Prints the shell prompt to stdout
 *
 * Return: void
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
 * read_line - Reads a line from standard input
 *
 * Uses getline to dynamically allocate memory for the input.
 * Strips the trailing newline character if present.
 *
 * Return: pointer to the line string, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - Forks and executes a command
 * @args: null-terminated array of arguments (args[0] is the command)
 * @argv0: name of the shell (for error messages)
 *
 * Searches PATH if the command has no slash. Does not fork
 * if the executable cannot be found.
 *
 * Return: exit status of the child, 127 if not found, -1 on fork error
 */
int execute_command(char **args, char *argv0)
{
	pid_t pid;
	int status;
	char *cmd_path = NULL;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n",
				argv0, args[0]);
			return (127);
		}
		cmd_path = args[0];
	}
	else
	{
		cmd_path = find_in_path(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n",
				argv0, args[0]);
			return (127);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (cmd_path != args[0])
			free(cmd_path);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n",
				argv0, args[0]);
			if (cmd_path != args[0])
				free(cmd_path);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd_path != args[0])
			free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (0);
}
