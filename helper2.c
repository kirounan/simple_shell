#include "shell.h"

int _read(info_t *info)
{
	ssize_t n_read = getline(&info->line, &info->len, stdin);

	if (n_read < 1)
	{
		free(info->line);
		free_list(&info->path);
		free(info->cwd);
		free_env(&info->env);
		free(info->full_cmd);

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);

		exit(info->status);
	}
	info->status = EXIT_SUCCESS;
	return (info->status);
}

void _perror(size_t argc, ...)
{
	va_list messages;
	char *str;

	va_start(messages, argc);
	while (argc--)
	{
		str = va_arg(messages, char*);
		if (!str)
			str = "";
		write(STDERR_FILENO, str, strlen(str));
		if (argc)
			write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, "\n", 1);
	va_end(messages);
}

void _num_to_str(char **buf, size_t n)
{
	if (n > 9)
		_num_to_str(buf, n/10);
	**buf = '0' + n % 10;
	*buf += 1;
	**buf = '\0';
}

int _isnumber(char *s)
{
	while (*s)
	{
		if (isdigit(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}
