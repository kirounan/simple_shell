#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * struct list - singly linked list
 * @str: pointer to dynamically-allocated string
 * @next: pointer to the next node
 */
typedef struct list
{
	char *str;
	struct list *next;
} list_t;

list_t *str_to_list(const char *str, char delimiter);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t **head);

ssize_t _strchr(const char *str, char c);

char **tokenize(const char *str);
size_t count_tokens(const char *str);
void free_tokens(char **tokens);

int _isspace(int c);

#endif
