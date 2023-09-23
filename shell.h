#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

#include "shell_macros.h"

extern char **environ;
extern int errno;

/**
 * struct al - alias data
 * @name: name of alias
 * @value: value to replace it with
 * @next: pointer to next node
 */
typedef struct al
{
	char *name;
	char *value;
	struct al *next;
} alias_list;

/**
 * struct od - Operation Data
 * @operands: The operands in the operation
 * @operators: The operators in the operation
 */
typedef struct od
{
	char **operands;
	int operators[MAX_TOKENS];
} ops_data;

/**
 * struct pd - Program Data
 * @name: Path of the shell when ran
 * @execution_count: Tracks the number of commands executed
 * @cmd: The current running command
 * @args: Current command arguments
 * @cmdline: The command read from stdin
 * @cmdlist: The commands available in a command line
 * @logic_data: Data related to the logical operation of a single command.
 * @al: Alias list
 * @cmdlinebuf: Buffer to store the expanded cmd line
 * @fd: File descriptor
 * @mode: Shell mode
 */
typedef struct pd
{
	char *name;
	int execution_count;
	char *cmd;
	char **args;
	char *cmdline;
	char **cmdlist;
	char cmdlinebuf[MAX_DIR_LENGTH];
	ops_data *logic_data;
	alias_list *al;
	int fd;
	int mode;

} sh_metadata;

/**
 * struct bf - Builtin-function
 * @cmd: The builtin command
 * @action: The function to handle the command
 */
typedef struct bf
{
	char *cmd;
	int (*action)(sh_metadata *data);
} builtin_action;


char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
char *_strtok(char *s, char *delim);
char *_strdup_range(char *src, int from, int to);
char *_strtrim(char *str);
int _isdigit(char *s);
void pt_array_freed(char **arr);
void free_prog_data(sh_metadata *data);
void _free(sh_metadata *data);
void free_all_aliases(alias_list *var);
ssize_t _read(sh_metadata *data);
void display_prompt(sh_metadata *data);
void _tokenise(sh_metadata *data);
char *_path(char *args);
int _command(char *args);
int _execute(sh_metadata *data);
void iterate_shell(sh_metadata *data);
int check_builtin(sh_metadata *data);
void _initialise(sh_metadata *data);
void compile_commands(sh_metadata *data);
int comment_section(sh_metadata *data);
ops_data *expand_logical_ops(char *cmd, ops_data *data);
char *expand_var(char *line, sh_metadata *data);
char *exp_alias(char *str, int ret, sh_metadata *data);
char *_get_environ(const char *name);
int _set_environ(char *var, char *val);
int _unset_environ(char *var);
int write_env(sh_metadata *data);
int _exitbuiltin(sh_metadata *data);
int _setenvbuiltin(sh_metadata *data);
int _unsetenvbuiltin(sh_metadata *data);
int _cd(sh_metadata *data);
int _aliasbuiltin(sh_metadata *data);
void add_alias(char *name, char *value, sh_metadata *data);
void print_alias(sh_metadata *data, char *names);
alias_list *get_alias(sh_metadata *data, char *name);
void print_error(sh_metadata *data);
ssize_t _print_err(char *err);
void number_to_string(char *buf, int num);
void reverse_string(char *str);
int _atoi(char *str);
void handle_sigint(int signal);

#endif
