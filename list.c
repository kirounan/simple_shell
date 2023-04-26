#include "list.h"

/**
 * str_to_list - turn a string into a linked list
 * @str: string passed
 * @delim: delimiter passed
 * Return: pointer to list
 */
list_t *str_to_list(const char *str, char delim)
{
	list_t *head = NULL;

	if (!str)
		return (NULL);

	if (!_str_to_list(&head, str, delim))
		free_list(&head);

	return (head);
}


/**
 * _str_to_list - turn a string into a linked list (helper)
 * @tailptr: pointer to the tail of the list
 * @str: string
 * @delim: delimiter
 *
 * Return: pointer to the tail of the list
 */
list_t *_str_to_list(list_t **tailptr, const char *str, char delim)
{
	list_t *tail;
	ssize_t len = _strchr(str, delim);

	if (len == -1)
		len = _strlen(str);

	tail = add_node_end(tailptr, NULL);
	if (!tail)
		return (NULL);

	tail->str = _memdup(str, len + 1);
	if (!tail->str)
		return (NULL);

	tail->str[len] = '\0';

	if (str[len])
		return (_str_to_list(&tail, str + len + 1, delim));

	return (tail);
}


/**
 * add_node - insert a string at the beginning of the list
 * @head: a pointer to the address of the first list node
 * @str: the string to add to the list
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new no
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;

	if (!head)
		return (NULL);

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = _strdup(str);
	new->next = *head;

	*head = new;

	return (new);
}


/**
 * add_node_end - add a string at the end of the list
 * @head: a pointer to the address of the first list node
 * @str: the string to add to the list
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new no
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

	new->str = _strdup(str);
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
