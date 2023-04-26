#include "command.h"


/**
 * add_cmd_end - add a command at the end of the list
 * @head: a pointer to the address of the first list node
 * @cmd: the cmd to add to the list
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new node.
 */
cmdlist_t *add_cmd_end(cmdlist_t **head, const char *cmd)
{
	cmdlist_t *new;

	if (!head)
		return (NULL);
	if (*head)
		return (add_cmd_end(&((*head)->next), cmd));

	new = malloc(sizeof(cmdlist_t));
	if (!new)
		return (NULL);

	new->next = NULL;
	new->tree = NULL;

	new->tokens = tokenize(cmd);
	if (!new->tokens)
	{
		free(new);
		return (NULL);
	}
	*head = new;

	return (new);
}


/**
 * del_cmd - remove a command from a command list
 * @head: the first node
 * @index: argument passed
 * Return: address of deleted node
 */
cmdlist_t *del_cmd(cmdlist_t **head, size_t index)
{
	cmdlist_t *old;

	if (!(head && *head))
		return (NULL);
	if (index)
		return (del_cmd(&((*head)->next), index - 1));

	old = *head;
	*head = (*head)->next;
	free_cmdtree(&(old->tree));
	free_tokens(&(old->tokens));
	free(old);

	return (old);
}


/**
 * pop_cmd - remove a node and retrieve it's tokens
 * @head: the first node
 * Return: command tokens
 */
char **pop_cmd(cmdlist_t **head)
{
	cmdlist_t *pop;
	char **tokens;

	if (!(head && *head))
		return (NULL);

	pop = *head;
	tokens = pop->tokens;
	*head = (*head)->next;

	free_cmdtree(&(pop->tree));
	free(pop);

	return (tokens);
}


/**
 * free_cmdlist - free a linked list and and set head to NULL
 * @head: the first node
 */
void free_cmdlist(cmdlist_t **head)
{
	if (head && *head)
	{
		free_cmdlist(&((*head)->next));
		free_cmdtree(&((*head)->tree));
		free_tokens(&((*head)->tokens));
		free(*head);
		*head = NULL;
	}
}
