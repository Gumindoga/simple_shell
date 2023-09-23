#include "shell.h"

/**
 * free_all_aliases - frees memory from alias
 * @var: pointer to head node
 */
void free_all_aliases(alias_list *var)
{
	alias_list *alias = var;
	alias_list *temp;

	while (alias != NULL)
	{
		temp = alias;
		alias = alias->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

/**
 * pt_array_freed - Frees a double pointer
 * @arr: The memory area to free
 * Return: void
 */
void pt_array_freed(char **arr)
{
	int i;

	if (!arr)
		return;

	for (i = 0; arr[i]; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}

/**
 * free_prog_data - Frees the program data
 * @data: Program data
 * Return: void
 */
void free_prog_data(sh_metadata *data)
{
	if (data->args)
		pt_array_freed(data->args);
	if (data->cmdline)
		free(data->cmdline);
	if (data->cmd)
		free(data->cmd);
	data->args = NULL;
	data->cmdline = NULL;
	data->cmd = NULL;
}

/**
 * _free - Frees all program data
 * @data: Program data
 * Return: void
 */
void _free(sh_metadata *data)
{
	if (data->cmdlist && data->mode == INTERACTIVE_MODE)
		pt_array_freed(data->cmdlist);

	if (data->fd != STDIN_FILENO)
	{
		if (close(data->fd))
			perror(data->name);
	}

	if (data->logic_data->operands)
		pt_array_freed(data->logic_data->operands);

	free_prog_data(data);
	pt_array_freed(environ);
	free_all_aliases(data->al);
}
