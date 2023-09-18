#include "bshell.h"

/**
 * cd_home - this changes the dir to home directory
 * @datash: data relevant (environ)
 * Return: nothing
 */
void cd_home(data_shell *datash)
{
	char *n_pwd;
	char *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	n_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", n_pwd, datash);
		free(n_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		in_ero(datash, 2);
		free(n_pwd);
		return;
	}

	set_env("OLDPWD", n_pwd, datash);
	set_env("PWD", home, datash);
	free(n_pwd);
	datash->status = 0;
}

/**
 * cd_in - this changes th dir to the parent directory
 * @datash: data operationals (environ)
 * Return: nothing
 */

void cd_in(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dr, *ps_pwd, *ps_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	ps_pwd = _strdup(pwd);
	set_env("OLDPWD", ps_pwd, datash);
	dr = datash->args[1];
	if (_strcmp(".", dr) == 0)
	{
		set_env("PWD", ps_pwd, datash);
		free(ps_pwd);
		return;
	}
	if (_strcmp("/", ps_pwd) == 0)
	{
		free(ps_pwd);
		return;
	}
	ps_strtok_pwd = ps_pwd;
	reverse_string(ps_strtok_pwd);
	ps_strtok_pwd = _strtok(ps_strtok_pwd, "/");
	if (ps_strtok_pwd != NULL)
	{
		ps_strtok_pwd = _strtok(NULL, "\0");

		if (ps_strtok_pwd != NULL)
			reverse_string(ps_strtok_pwd);
	}
	if (ps_strtok_pwd != NULL)
	{
		chdir(ps_strtok_pwd);
		set_env("PWD", ps_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(ps_pwd);
}

/**
 * cd_go - this changes the dir to a directory given
 * by the user
 * @datash: data operations (directories)
 * Return: nothing
 *
 */

void cd_go(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dr, *ps_pwd, *ps_dr;

	getcwd(pwd, sizeof(pwd));

	dr = datash->args[1];
	if (chdir(dr) == -1)
	{
		in_ero(datash, 2);
		return;
	}
	ps_pwd = _strdup(pwd);
	set_env("OLDPWD", ps_pwd, datash);
	ps_dr = _strdup(dr);
	set_env("PWD", ps_dr, datash);

	free(ps_pwd);
	free(ps_dr);

	datash->status = 0;

	chdir(dr);
}

/**
 * cd_before - this changes the dir to the previous directory
 * @datash: data operation (environ)
 * Return: nothing
 *
 */
void cd_before(data_shell *datash)
{
	char pwd[PATH_MAX], *ps_pwd;
	char *n_pwd, *n_oldpwd;
	char *ps_oldpwd;

	getcwd(pwd, sizeof(pwd));
	ps_pwd = _strdup(pwd);

	n_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (n_oldpwd == NULL)
		ps_oldpwd = ps_pwd;
	else
		ps_oldpwd = _strdup(n_oldpwd);

	set_env("OLDPWD", ps_pwd, datash);

	if (chdir(ps_oldpwd) == -1)
		set_env("PWD", ps_pwd, datash);
	else
		set_env("PWD", ps_oldpwd, datash);

	n_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, n_pwd, _strlen(n_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(ps_pwd);
	if (n_oldpwd)
		free(ps_oldpwd);

	datash->status = 0;

	chdir(n_pwd);
}
