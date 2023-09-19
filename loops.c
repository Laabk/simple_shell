#include "bshell.h"


/**
 * execute_line - this finds all builtins and commands
 * @datash: data operation
 * Return: 1 for success.
 */

int execute_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (execute_cmd(datash));
}

/**
 * _comments - this func deletes comments from the input
 * @se: the input string involved
 * Return: without comments
 */

char *_comments(char *se)
{
	int d, sh_pr;

	sh_pr = 0;
	for (d = 0; se[d]; d++)
	{
		if (se[d] == '#')
		{
			if (d == 0)
			{
				free(se);
				return (NULL);
			}

			if (se[d - 1] == ' ' || se[d - 1] == '\t' || se[d - 1] == ';')
				sh_pr = d;
		}
	}

	if (sh_pr != 0)
	{
		se = _realloc(se, d, sh_pr + 1);
		se[sh_pr] = '\0';
	}

	return (se);
}

/**
 * _loops - the shell Loop
 * @datash: data operationals(av, input, args)
 * Return: nothing
 */

void _loops(data_shell *datash)
{
	int lope;
	int d_eag;
	char *feed;

	lope = 1;
	while (lope == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		feed = read_line(&d_eag);
		if (d_eag != -1)
		{
			feed = _comments(feed);
			if (feed == NULL)
				continue;

			if (check_syntaxero(datash, feed) == 1)
			{
				datash->status = 2;
				free(feed);
				continue;
			}
			feed = rep_var(feed, datash);
			lope = func_sort_commands(datash, feed);
			datash->counter += 1;
			free(feed);
		}
		else
		{
			lope = 0;
			free(feed);
		}
	}
}
