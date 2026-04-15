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
 * resolve_cmd - Resolves the full path of a command
 * @args: null-terminated argument array, args[0] is the command
 * @argv0: shell name for error messages
 *
 * Return: full path string (may be args[0] itself), or NULL if not found
 */
static char *resolve_cmd(char **args, char *argv0)
{
	char *cmd_path = NULL;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n",
				argv0, args[0]);
			return (NULL);
		}
		return (args[0]);
	}

	cmd_path = find_in_path(args[0]);
	if (cmd_path == NULL)
		fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);

	return (cmd_path);
}

/**
 * fork_and_exec - Forks a child and runs the command via execve
 * @cmd_path: resolved executable path
 * @args: null-terminated argument array
 * @argv0: shell name for error messages
 *
 * Return: exit status of the child, or 1 on abnormal termination
 */
static int fork_and_exec(char *cmd_path, char **args, char *argv0)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
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

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * execute_command - Resolves and executes a command
 * @args: null-terminated array of arguments (args[0] is the command)
 * @argv0: name of the shell (for error messages)
 *
 * Does not fork if the command cannot be found.
 *
 * Return: exit status of the child, 127 if not found, -1 on fork error
 */
int execute_command(char **args, char *argv0)
{
	char *cmd_path = NULL;
	int status = 0;

	cmd_path = resolve_cmd(args, argv0);
	if (cmd_path == NULL)
		return (127);

	status = fork_and_exec(cmd_path, args, argv0);

	if (cmd_path != args[0])
		free(cmd_path);

	return (status);
}
