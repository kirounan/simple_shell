#include "shell.h"


/**
 * add_node - insert a string at the beginning of the list
 * @head: a pointer to the address of the first list node
 * @str: the string to add to the list
 * Return: If memory allocation fails, return NULL
 * Otherwise, return the address of the new one
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;

	if (!head)
		return (NULL);

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = strdup(str);
	new->next = *head;

	*head = new;

	return (new);
}


/**
 * add_node_end - add a string at the end of the list
 * @head: a pointer to the address of the first list node
 * @str: the string to add to the list
 * Return: If memory allocation fails, return NULL
 * Otherwise, return the address of the new one
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new;

	if (!head)
		return (NULL);

	if (*head)
		return (add_node_end(&((*head)->next), str));

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = strdup(str);
	new->next = *head;

	*head = new;

	return (new);
}


/**
 * free_list - free a linked list and and set head to NULL
 * @head: the first list node
 */
void free_list(list_t **head)
{
	if (!*head)
		return;

	free_list(&((*head)->next));
	free((*head)->str);
	free(*head);
	*head = NULL;
}

/**
 * strchr - get the index of the first matching character
 */
ssize_t _strchr(const char *str, char c)
{
	size_t pos;

	if (!str)
		return (-1);

	pos = 0;
	while (str[pos] && str[pos] != c)
		++pos;

	return (pos);
}
/**
 * str_to_list - turn a string into a linked list
 */
list_t *str_to_list(const char *str, char delimiter)
{
	list_t *head = NULL;
	list_t *tail = NULL;
	size_t len;

	if (!str)
		return (NULL);

	while (*str)
	{
		len = _strchr(str, delimiter);
		tail = add_node_end(&head, NULL);
		if (!tail)
		{
			free_list(&head);
			return (NULL);
		}

		tail->str = malloc(sizeof(char *) * len + 1);
		if (!tail->str)
		{
			free_list(&head);
			return (NULL);
		}
		memcpy(tail->str, str, len);
		tail->str[len] = '\0';

		if (str[len])
			str += len + 1;
		else
			str += len;
	}

	return (head);
}
