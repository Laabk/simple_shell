#include "bshell.h"

/**
 * sh_helps - this function retrieves any help messages according builtin
 * @datash: the data operation
 * Return: always 0
*/

int sh_helps(data_shell *datash)
{

	if (datash->args[1] == 0)
		generalhelps();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		setenvihelps();
	else if (_strcmp(datash->args[1], "env") == 0)
		envihelps();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		unsetenvihelps();
	else if (_strcmp(datash->args[1], "help") == 0)
		helps();
	else if (_strcmp(datash->args[1], "exit") == 0)
		exithelps();
	else if (_strcmp(datash->args[1], "cd") == 0)
		cdhelps();
	else if (_strcmp(datash->args[1], "alias") == 0)
		aliashelps();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
