#include "bshell.h"

/**
 * sh_exit - this funct exits the shell
 * @datash: data operation (status and args)
 * Return: 0 for success.
 */

int sh_exit(data_shell *datash)
{
	unsigned int ust;
	int dgt, str_leng, numbess;

	if (datash->args[1] != NULL)
	{
		ust = i_atoi(datash->args[1]);
		dgt = _isdigit(datash->args[1]);
		str_leng = _strlen(datash->args[1]);
		numbess = ust > (unsigned int)INT_MAX;
		if (!dgt || str_leng > 10 || numbess)
		{
			in_ero(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ust % 256);
	}
	return (0);
}
