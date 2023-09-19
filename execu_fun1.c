#include "bshell.h"

/**
 * cd_cddir - this funct checks ":" if is in the current directory.
 * @path: pointer char type
 * @d: ointer of index.
 * Return: 1 for path searchable in the cd, 0 otherwise.
 */

int cd_cddir(char *path, int *d)
{
	if (path[*d] == ':')
		return (1);

	while (path[*d] != ':' && path[*d])
	{
		*d += 1;
	}

	if (path[*d])
		*d += 1;

	return (0);
}

/**
 * func_which - this funct locates a command to be exec
 * @cmd: the command name passed
 * @_environ: thee environment variable
 * Return: command addresss
 */

char *func_which(char *cmd, char **_environ)
{
	struct stat st;
	char *path, *pt_path, *tkn_path, *dr;
	int leng_dr, leng_cmd, d;

	path = _getenv("PATH", _environ);
	if (path)
	{
		pt_path = _strdup(path);
		leng_cmd = _strlen(cmd);
		tkn_path = _strtok(pt_path, ":");
		d = 0;
		while (tkn_path != NULL)
		{
			if (cd_cddir(path, &d))
				if (stat(cmd, &st) == 0)
					return (cmd);
			leng_dr = _strlen(tkn_path);
			dr = malloc(leng_dr + leng_cmd + 2);
			_strcpy(dr, tkn_path);
			_strcat(dr, "/");
			_strcat(dr, cmd);
			_strcat(dr, "\0");
			if (stat(dr, &st) == 0)
			{
				free(pt_path);
				return (dr);
			}
			free(dr);
			tkn_path = _strtok(NULL, ":");
		}
		free(pt_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * func_execute - this func determines if a funct is an executable
 * @datash: data operation
 * Return: 0 for an executable, other number if it does
 */

int func_execute(data_shell *datash)
{
	char *feed;
	struct stat st;
	int d;

	feed = datash->args[0];
	for (d = 0; feed[d]; d++)
	{
		if (feed[d] == '.')
		{
			if (feed[d + 1] == '.')
				return (0);
			if (feed[d + 1] == '/')
				continue;
			else
				break;
		}
		else if (feed[d] == '/' && d != 0)
		{
			if (feed[d + 1] == '.')
				continue;
			d++;
			break;
		}
		else
			break;
	}
	if (d == 0)
		return (0);

	if (stat(feed + d, &st) == 0)
	{
		return (d);
	}
	in_ero(datash, 127);
	return (-1);
}

/**
 * ero_cmd - this func checkes if user has permissions to access
 * @dr: the destination directory
 * @datash: the data operations
 * Return: 1 for an error, 0 if not
 */

int ero_cmd(char *dr, data_shell *datash)
{
	if (dr == NULL)
	{
		in_ero(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dr) != 0)
	{
		if (access(dr, X_OK) == -1)
		{
			in_ero(datash, 126);
			free(dr);
			return (1);
		}
		free(dr);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			in_ero(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_cmd - this func executes the command lines
 * @datash: data operation (args and input)
 * Return: 1 for success.
 */

int execute_cmd(data_shell *datash)
{
	pid_t padr, cpad;
	int sta, exk;
	char *dr;
	(void) cpad;

	exk = func_execute(datash);
	if (exk == -1)
		return (1);
	if (exk == 0)
	{
		dr = func_which(datash->args[0], datash->_environ);
		if (ero_cmd(dr, datash) == 1)
			return (1);
	}

	padr = fork();
	if (padr == 0)
	{
		if (exk == 0)
			dr = func_which(datash->args[0], datash->_environ);
		else
			dr = datash->args[0];
		execve(dr + exk, datash->args, datash->_environ);
	}
	else if (padr < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			cpad = waitpid(padr, &sta, WUNTRACED);
		} while (!WIFEXITED(sta) && !WIFSIGNALED(sta));
	}

	datash->status = sta / 256;
	return (1);
}
