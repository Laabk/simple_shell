#include "bshell.h"

/**
 * get_builtin - this func calls builtin that are the command in the arg
 * @cmd: the command mode
 * Return: pointer of builtin command
 *
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	int d;

	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", sh_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_to_shell },
		{ "help", sh_helps },
		{ NULL, NULL }
	};

	for (d = 0; builtin[d].name; d++)
	{
		if (_strcmp(builtin[d].name, cmd) == 0)
			break;
	}

	return (builtin[d].f);
}
