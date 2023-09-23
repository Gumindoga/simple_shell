#include "shell.h"

/**
 * write_env - Handles the `env` built-in command
 * @data: Program data
 * Return: The status of the execution
 */
int write_env(sh_metadata *data)
{
	int i = 0;

	(void)data;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	errno = 0;
	return (EXIT_SUCCESS);
}

/**
 * _exitbuiltin - Handles the builtin exit command
 * @data: Program data
 * Return: Nothing
 */
int _exitbuiltin(sh_metadata *data)
{
	int status = errno; /*this is the default exit status */

	if (data->args[1] != NULL)
	{
		status = _atoi(data->args[1]);
		if (!_isdigit(data->args[1]) || status < 0)
		{
			errno = 2;
			if (isatty(STDIN_FILENO))
				return (-1);
			print_error(data);
			status = 2;
		}
	}

	_free(data);
	exit(status);
}
/**
 * _setenvbuiltin - Initialize a new environment variable
 * @data: program data
 * Return: 0 if successful otherwise, -1
 */
int _setenvbuiltin(sh_metadata *data)
{
	int temp = _set_environ(data->args[1], data->args[2]);

	return (temp);
}
/**
 *  _unsetenvbuiltin - deletes an existing env variable
 *  @data: Program data
 *  Return: 0 if successful
 */
int _unsetenvbuiltin(sh_metadata *data)
{
	int temp = _unset_environ(data->args[1]);

	return (temp);
}

/**
 * _cd - Handles the cd command
 * @data: Program data
 * Return: The status of the execution
 */
int _cd(sh_metadata *data)
{
	char *dir = data->args[1];
	char pwd[1024], *home;
	int status, is_prev = 0;

	getcwd(pwd, 1024);
	home = _get_environ("HOME");

	/* Check if no argument */
	if (dir == NULL)
		dir = home ? home : pwd;

	/* Check if the argument is - */
	if (_strcmp(dir, "-") == 0)
	{
		is_prev = 1;
		/* cd to the OLDPWD if it exist else PWD */
		dir = _get_environ("OLDPWD");
		if (!dir)
			dir = pwd;
	}

	status = chdir(dir);
	if (status == EXIT_SUCCESS)
	{
		_set_environ("OLDPWD", pwd);
		getcwd(pwd, 1024);
		_set_environ("PWD", pwd);
		if (is_prev)
			write(STDOUT_FILENO, pwd, _strlen(pwd)), write(STDOUT_FILENO, "\n", 1);
	}

	return (status);
}
