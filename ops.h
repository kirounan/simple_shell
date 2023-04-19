#ifndef OPS_H
#define OPS_H

static built_in_t ops[] = {
	{"env", _env, "Usage: env"},
	{"exit", exit_, "Usage: exit"},
	{"setenv", _setenv, "Usage: setenv VARIABLE VALUE"},
	{"unsetenv", _unsetenv, "Usage: unsetenv VARIABLE"},
	{NULL, NULL, NULL}
};

#endif
