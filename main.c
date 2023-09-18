#include "bshell.h"

/**
 * free_data - frees data operations and structs
 * @datash: data operations
 * Return: nothing
 */

void free_data(data_shell *datash)
{
	unsigned int d;

	for (d = 0; datash->_environ[d]; d++)
	{
	free(datash->_environ[d]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - this sets the data structure
 * @datash: data operations
 * @av: the argument vector involved
 * Return: nothing
 */

void set_data(data_shell *datash, char **av)
{
	unsigned int d;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (d = 0; environ[d]; d++)
		;

	datash->_environ = malloc(sizeof(char *) * (d + 1));

	for (d = 0; environ[d]; d++)
	{
		datash->_environ[d] = _strdup(environ[d]);
	}

	datash->_environ[d] = NULL;
	datash->pid = a_itoa(getpid());
}

/**
 * main - the point of entry for the shell data
 * @ac: argument list that is involved
 * @av: argument vector involved
 * Return: 0 for success.
 */

int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, _visio);
	set_data(&datash, av);
	_loops(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
