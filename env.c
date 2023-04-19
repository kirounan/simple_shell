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
