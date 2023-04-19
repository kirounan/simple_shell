#include "shell.h"

char *strjoin(char *s1, char *s2, char c)
{
	char *new_s;
	ssize_t s1_len, s2_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";

	s1_len = strlen(s1);
	s2_len = strlen(s2);

	new_s = malloc(s1_len + s2_len + 2);
	if (!new_s)
		return (NULL);
	strcpy(new_s, s1);
	new_s[s1_len] = c;
	strcpy(new_s + s1_len + 1, s2);

	return (new_s);
}

/**
 * strchr - get the index of the first matching character
 */
ssize_t _strchr(const char *str, char c)
{
	size_t pos;

	if (!str)
		return (-1);
	for (pos = 0; str[pos]; ++pos)
	{
		if (str[pos] == c)
			return (pos);
	}
	return (-1);
}

