#include "bshell.h"

/**
 * shell_envir_name - this func compares the env variables names
 * with name used.
 * @nenv: environment name variable
 * @name: the name used
 * Return: 0 for not equal. Another value if they are.
 */

int shell_envir_name(const char *nenv, const char *name)
{
	int d;

	for (d = 0; nenv[d] != '='; d++)
	{
		if (nenv[d] != name[d])
		{
			return (0);
		}
	}

	return (d + 1);
}

/**
 * _getenv - this func gets an environment variable
 * @name: name environment variable used
 * @_environ: the environment variable passed
 * Return: environment variable value if is found.
 * In other case, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *pt_envir;
	int d, go;

	pt_envir = NULL;
	go = 0;

	for (d = 0; _environ[d]; d++)
	{
		go = shell_envir_name(_environ[d], name);
		if (go)
		{
			pt_envir = _environ[d];
			break;
		}
	}

	return (pt_envir + go);
}

/**
 * _env - this prints the evironment variables
 * @datash: data operation.
 * Return: 1 for  success.
 */

int _env(data_shell *datash)
{
	int d, b;

	for (d = 0; datash->_environ[d]; d++)
	{

		for (b = 0; datash->_environ[d][b]; b++)
			;

		write(STDOUT_FILENO, datash->_environ[d], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
