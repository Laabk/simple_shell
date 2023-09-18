#include "bshell.h"

/**
 * copy_info - this func copies an info to create a alias
 * @name: the name passed
 * @value: the value passed
 * Return: aqn alias.
 */

char *copy_info(char *name, char *value)
{
	char *nw;
	int leng_name;
	int leng_value, leng;

	leng_name = _strlen(name);
	leng_value = _strlen(value);
	leng = leng_name + leng_value + 2;
	nw = malloc(sizeof(char) * (leng));
	_strcpy(nw, name);
	_strcat(nw, "=");
	_strcat(nw, value);
	_strcat(nw, "\0");

	return (nw);
}

/**
 * set_env - this func sets an environment variable for call
 * @name: environment name variable
 * @value: environment vvalue ariable
 * @datash: data operation (environ)
 * Return: nothing
 */

void set_env(char *name, char *value, data_shell *datash)
{
	int d;
	char *var_envron;
	char *name_envron;

	for (d = 0; datash->_environ[d]; d++)
	{
		var_envron = _strdup(datash->_environ[d]);
		name_envron = _strtok(var_envron, "=");
		if (_strcmp(name_envron, name) == 0)
		{
			free(datash->_environ[d]);
			datash->_environ[d] = copy_info(name_envron, value);
			free(var_envron);
			return;
		}
		free(var_envron);
	}

	datash->_environ = _reallocab(datash->_environ, d, sizeof(char *) * (d + 2));
	datash->_environ[d] = copy_info(name, value);
	datash->_environ[d + 1] = NULL;
}

/**
 * _setenv - this func compares env variables names with
 * name used
 * @datash: data operation
 * Return: 1 for success.
 */

int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		in_ero(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - this funcdeletes a passed environment variable
 * @datash: data operations (env name)
 * Return: 1 for  success.
 */
int _unsetenv(data_shell *datash)
{
	char **reloc_env;
	char *var_envron, *name_envron;
	int d, b, g;

	if (datash->args[1] == NULL)
	{
		in_ero(datash, -1);
		return (1);
	}
	g = -1;
	for (d = 0; datash->_environ[d]; d++)
	{
		var_envron = _strdup(datash->_environ[d]);
		name_envron = _strtok(var_envron, "=");
		if (_strcmp(name_envron, datash->args[1]) == 0)
		{
			g = d;
		}
		free(var_envron);
	}
	if (g == -1)
	{
		in_ero(datash, -1);
		return (1);
	}
	reloc_env = malloc(sizeof(char *) * (d));
	for (d = b = 0; datash->_environ[d]; d++)
	{
		if (d != g)
		{
			reloc_env[b] = datash->_environ[d];
			b++;
		}
	}
	reloc_env[b] = NULL;
	free(datash->_environ[g]);
	free(datash->_environ);
	datash->_environ = reloc_env;
	return (1);
}
