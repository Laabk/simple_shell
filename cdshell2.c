#include "bshell.h"

/**
 * cd_to_shell - this changes the dir to the current directory
 * @datash: data operations
 * Return: 1 on success
 */

int cd_to_shell(data_shell *datash)
{
	char *dr;
	int shhome;
	int shhome2, shddash;

	dr = datash->args[1];

	if (dr != NULL)
	{
		shhome = _strcmp("$HOME", dr);
		shhome2 = _strcmp("~", dr);
		shddash = _strcmp("--", dr);
	}

	if (dr == NULL || !shhome || !shhome2 || !shddash)
	{
		cd_home(datash);
		return (1);
	}
	if (_strcmp("-", dr) == 0)
	{
		cd_before(datash);
		return (1);
	}
	if (_strcmp(".", dr) == 0 || _strcmp("..", dr) == 0)
	{
		cd_in(datash);
		return (1);
	}
	cd_go(datash);
	return (1);
}
