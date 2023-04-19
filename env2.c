#include "shell.h"

my_env_t *add_env_node_end(my_env_t **head, const char *key, const char *value)
{
	my_env_t *new;

	if (!head)
		return (NULL);

	if (*head)
		return (add_env_node_end(&((*head)->next), key, value));

	new = malloc(sizeof(my_env_t));
	if (!new)
		return (NULL);

	new->key = strdup(key);
	new->value = strdup(value);
	new->next = NULL;

	*head = new;
	return (new);
}

int _unsetenv(info_t *info)
{
	char *cmd_num;
	size_t i;

	if (!info->tokens[1])
	{
		cmd_num = num_to_str(info->cmd_num);
		_perror(4, info->argv[0], cmd_num, info->tokens[0], "Too few arguments.");
		free(cmd_num);
		info->status = 1;
		return (info->status);
	}
	for (i = 1; info->tokens[i]; i++)
		del_env_node(&info->env, info->tokens[i]);
	info->status = 0;
	return (info->status);
}

int _setenv(info_t *info)
{
	my_env_t *var;
	char *value = "";
	char *cmd_num;

	if (!info->tokens[1])
		return(_env(info));

	if (info->tokens[2])
	{
		if (info->tokens[3])
		{
			cmd_num = num_to_str(info->cmd_num);
			_perror(4, info->argv[0], cmd_num, info->tokens[0], "Too many arguments.");
			free(cmd_num);
			info->status = 1;
			return (info->status);
		}
		value = info->tokens[2];
	}

	var = find_env_node(info->env, info->tokens[1]);

	if (!var)
		add_env_node_end(&info->env, info->tokens[1], value);
	else
	{
		free(var->value);
		var->value = strdup(value);
	}
	info->status = 0;

	return (info->status);
}
