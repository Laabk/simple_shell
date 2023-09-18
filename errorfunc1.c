#include "bshell.h"

/**
 * in_ero - this func calls the error according the builtininvolved
 * syntax or permission
 * @datash: data operation with passed arguments
 * @eval: the error value encountered
 * Return: the error
 */

int in_ero(data_shell *datash, int eval)
{
	char *ero;

	switch (eval)
	{
	case -1:
		ero = ero_env(datash);
		break;
	case 126:
		ero = ero_path_126(datash);
		break;
	case 127:
		ero = ero_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			ero = ero_sh_exit(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			ero = ero_in_cd(datash);
		break;
	}

	if (ero)
	{
		write(STDERR_FILENO, ero, _strlen(ero));
		free(ero);
	}

	datash->status = eval;
	return (eval);
}

/**
 * ero_env - the error message display for env in get_env.
 * @datash: data operations (counter, arguments)
 * Return: an error message.
 */

char *ero_env(data_shell *datash)
{
	char *v_str, *mesg;
	int len;
	char *ero;

	v_str = a_itoa(datash->counter);
	mesg = ": Unable to add/remove from environment\n";
	len = _strlen(datash->av[0]) + _strlen(v_str);
	len += _strlen(datash->args[0]) + _strlen(mesg) + 4;
	ero = malloc(sizeof(char) * (len + 1));
	if (ero == 0)
	{
		free(ero);
		free(v_str);
		return (NULL);
	}

	_strcpy(ero, datash->av[0]);
	_strcat(ero, ": ");
	_strcat(ero, v_str);
	_strcat(ero, ": ");
	_strcat(ero, datash->args[0]);
	_strcat(ero, mesg);
	_strcat(ero, "\0");
	free(v_str);

	return (ero);
}

/**
 * ero_path_126 - the error message during path and failure denied permission.
 * @datash: the data operations (counter, arguments)
 * Return: error of string.
 */

char *ero_path_126(data_shell *datash)
{
	char *ero;
	int len;
	char *v_str;

	v_str = a_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(v_str);
	len += _strlen(datash->args[0]) + 24;
	ero = malloc(sizeof(char) * (len + 1));
	if (ero == 0)
	{
		free(ero);
		free(v_str);
		return (NULL);
	}
	_strcpy(ero, datash->av[0]);
	_strcat(ero, ": ");
	_strcat(ero, v_str);
	_strcat(ero, ": ");
	_strcat(ero, datash->args[0]);
	_strcat(ero, ": Permission denied\n");
	_strcat(ero, "\0");
	free(v_str);
	return (ero);
}
