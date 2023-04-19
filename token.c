#include "shell.h"


/**
 * _isspace - check if a character is whitespace
 * @c: input charachter
 * Return: If c is a whitespace character, return 1
 * else return 0
 */
int _isspace(int c)
{
	return (c == ' ' || (c >= 0x09 && c <= 0x0d));
}

/**
 * count_tokens - count the words in a string
 * @str: input string
 * Return: If str is NULL, return -1
 * Otherwise, return the number of words in string
 */
size_t count_tokens(const char *str)
{
	size_t i;

	if (!str)
		return (0);

	for (i = 0; *str; i++)
	{
		while (_isspace(*str))
			++str;
		if (!*str)
			break;
		do {
			++str;
		} while (*str && !_isspace(*str));
	}

	return (i);
}


/**
 * free_tokens - free an array of strings
 * @tokens: input array
 */
void free_tokens(char **tokens)
{
	char **current;

	if (!tokens)
		return;

	current = tokens;
	while (*current)
		free(*current++);
	free(tokens);
}


/**
 * tokensize - split a string into words (tokens)
 * @str: the string to tokenize
 *
 * Return: If malloc fails or if str is NULL or contains no tokens, return NULL
 * Otherwise, return an array containing the tokens in str, terminated by NULL
 */
char **tokenize(const char *str)
{
	char **tokens;
	size_t tok_count, tok_len;

	tok_count = count_tokens(str);
	if (!tok_count)
		return (NULL);

	tokens = malloc(sizeof(char *) * (tok_count + 1));
	if (!tokens)
		return (NULL);

	for (tok_count = 0; *str; ++tok_count)
	{
		while (_isspace(*str))
			++str;
		if (!*str)
			break;

		tok_len = 1;
		while (str[tok_len] && !_isspace(str[tok_len]))
			++tok_len;

		tokens[tok_count] = malloc(sizeof(char) * (tok_len + 1));

		if (!tokens[tok_count])
		{
			free_tokens(tokens);
			return (NULL);
		}

		tokens[tok_count][tok_len] = '\0';
		memcpy(tokens[tok_count], str, tok_len);

		str += tok_len;
	}
	tokens[tok_count] = NULL;

	return (tokens);
}
