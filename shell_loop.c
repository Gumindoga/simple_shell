#include "shell.h"

/**
 * display_prompt - Shows the prompt
 * @data: Program data
 * Return: void
 */
void display_prompt(sh_metadata *data)
{
	if (data->mode == INTERACTIVE_MODE)
		write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));
}

/**
 * run_command - Runs a single command
 * @data: Program data
 * Return: void
 */
void run_command(sh_metadata *data)
{
	int builtin, error_no;
	int i;
	ops_data logic_data;

	expand_logical_ops(data->cmd, &logic_data);

	for (i = 0; logic_data.operands[i]; i++)
	{
		/* Check operation */
		if (i > 0)
		{
			if (logic_data.operators[i - 1] == LOGICAL_AND && errno != 0)
				break;
			if (logic_data.operators[i - 1] == LOGICAL_OR && errno == 0)
				break;
		}

		data->logic_data = &logic_data;
		data->cmd = _strtrim(_strdup(logic_data.operands[i]));
		_tokenise(data);

		builtin = error_no = check_builtin(data);

		if (builtin == NOT_BUILTIN)
			error_no = _execute(data);

		if (error_no != EXIT_SUCCESS)
			print_error(data);

		/* Free the data for the current command */
		free_prog_data(data);
	}

	/* Free operands */
	pt_array_freed(logic_data.operands);
}

/**
 * iterate_shell - Main shell
 * @data: Data of the shell
 */
void iterate_shell(sh_metadata *data)
{
	ssize_t cmd_length, i;

	errno = 0; /* Set the initial errno */

	while (++(data->execution_count))
	{
		display_prompt(data);
		cmd_length = _read(data);

		if (cmd_length == 0)
			continue;

		compile_commands(data);

		for (i = 0; data->cmdlist[i]; ++i)
		{
			data->cmd = data->cmdlist[i];
			if (comment_section(data))
			{
				if (!data->cmd[0])
					errno = 0, free_prog_data(data);
				else
					run_command(data);
				break;
			}

			run_command(data);
		}

		/* Free the command list */
		pt_array_freed(data->cmdlist);
	}
}
