#include "shell.h"
#include "ops.h"

char *num_to_str(size_t n)
{
	size_t tmp = n, len = 1;
	char *buf;

	while (tmp /= 10)
		len++;
	buf = malloc(len + 1);
	if (!buf)
		return (NULL);
	_num_to_str(&buf, n);
	return (buf - len);
}
char **listtoenv(my_env_t *head)
{
	char **env;
	size_t len = 0;
	my_env_t *tmp = head;

	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	env = malloc(sizeof(char*) * (len + 1));
	if (!env)
		return (NULL);
	for (len = 0; head; len++)
	{
		env[len] = strjoin(head->key, head->value, '=');
		head = head->next;
	}
	env[len] = NULL;
	return (env);
}

int exit_(info_t *info)
{
	char *cmd_num;

	if (info->tokens[1])
	{
		if (_isnumber(info->tokens[1]) != 0)
			info->status = atoi(info->tokens[1]);
		else
		{

			cmd_num = num_to_str(info->cmd_num);
			_perror(5, info->argv[0], cmd_num, info->tokens[0], "Illegal number", info->tokens[1]);
			free(cmd_num);
			info->status = 2;
			return (info->status);
		}
	}
	free(info->line);
	free_list(&info->path);
	free(info->cwd);
	free_env(&info->env);
	free(info->full_cmd);
	free_tokens(info->tokens);

	exit(info->status);
	return (0);
}

void _sigint()
{
	write(STDERR_FILENO, "\n$ ", 3);
}

int _run(info_t *info)
{
	ssize_t i;
	char *cmd_num;

	for (i = 0; ops[i].name; i++)
	{
		if (!strcmp(info->tokens[0], ops[i].name))
			return (ops[i].f(info));
	}
	if (_strchr(info->tokens[0], '/') == -1)
		info->full_cmd = search_path(info, info->path);
	else
		info->full_cmd = strdup(info->tokens[0]);
	if (info->full_cmd)
		return (_exec(info));

	cmd_num = num_to_str(info->cmd_num);
	_perror(4, info->argv[0], cmd_num, info->tokens[0], "not found");
	free(cmd_num);
	return (-1);
}
