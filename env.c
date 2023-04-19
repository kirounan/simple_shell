#include "shell.h"


/** getenv - get a string from the environment
 * @name: input string
 * Return: the enviroment string
 */
char *_getenv(const char *name)
{
	char **env = environ;
	ssize_t pos;

	if (!(name && env))
		return (NULL);

	while (*env)
	{
		pos = _strchr(*env, '=');
		if (!strncmp(*env, name, pos))
			return (*env + pos + 1);
		++env;
	}

	return (NULL);
}
/**
 * free_env - free a linked list and and set head to NULL
 * @head: the first list node
 */
void free_env(my_env_t **head)
{
	if (!*head)
		return;

	free_env(&((*head)->next));
	free((*head)->key);
	free((*head)->value);
	free(*head);
	*head = NULL;
}
my_env_t *find_env_node(my_env_t *head, const char *key)
{
	if (!head)
		return (NULL);
	if (!strcmp(head->key, key))
		return (head);
	return (find_env_node(head->next, key));
}

my_env_t *del_env_node(my_env_t **head, const char *key)
{
	my_env_t *tmp;
	if  (!(head && *head))
		return (NULL);
	if (!strcmp((*head)->key, key))
	{
		tmp = *head;
		(*head) = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	else
		del_env_node(&((*head)->next), key);
	return (*head);
}

my_env_t *envtolist(char **env)
{
	char *env_str;
	my_env_t *head = NULL;
	size_t key_len = 0;

	while (*env)
	{
		env_str = strdup(*env);
		key_len = _strchr(*env, '=');
		env_str[key_len] = '\0';
		add_env_node_end(&head, env_str, env_str + key_len + 1);
		free(env_str);
		env++;
	}
	return (head);
}

int _env(info_t *info)
{
	my_env_t *var = info->env;

	while (var)
	{
		if (var->key)
			write(STDOUT_FILENO, var->key, strlen(var->key));
		write(STDOUT_FILENO, "=", 1);
		if (var->value)
			write(STDOUT_FILENO, var->value, strlen(var->value));
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}

	info->status = EXIT_SUCCESS;
	return (info->status);
}
