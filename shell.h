#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* shell.c */
void display_prompt(void);
char *read_line(void);
int execute_command(char **args, char *argv0);

/* args.c */
char **split_line(char *line);

/* path.c */
char *find_in_path(char *cmd);

/* builtins.c */
int handle_builtins(char **args);
void builtin_env(void);

/* utils.c */
int _strlen(const char *s);
char *_strdup(const char *s);
char *_getenv(const char *name);

/* free.c */
void free_args(char **args);
void free_path(char *path, char *original);

#endif /* SHELL_H */
