#include "bshell.h"

/**
 * ero_sh_exit - the generic error message for exit in the get_exit
 * @datash: data operations (counter, arguments)
 * Return: an error message
 */

char *ero_sh_exit(data_shell *datash)
{
	int len;
	char *ero, *v_str;

	v_str = a_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(v_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	ero = malloc(sizeof(char) * (len + 1));
	if (ero == 0)
	{
		free(v_str);
		return (NULL);
	}
	_strcpy(ero, datash->av[0]);
	_strcat(ero, ": ");
	_strcat(ero, v_str);
	_strcat(ero, ": ");
	_strcat(ero, datash->args[0]);
	_strcat(ero, ": Illegal number: ");
	_strcat(ero, datash->args[1]);
	_strcat(ero, "\n\0");
	free(v_str);

	return (ero);
}


/**
 * concate_cd - this function concatenates message for the cd error
 * @datash: data operation (directory)
 * @v_str: counter lines used
 * @ero: the output message
 * @mesg: the message to print out
 * Return: an error message
 */

char *concate_cd(data_shell *datash, char *mesg, char *ero, char *v_str)
{
	char *illegal_flag;

	_strcpy(ero, datash->av[0]);
	_strcat(ero, ": ");
	_strcat(ero, v_str);
	_strcat(ero, ": ");
	_strcat(ero, datash->args[0]);
	_strcat(ero, mesg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(ero, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(ero, datash->args[1]);
	}

	_strcat(ero, "\n");
	_strcat(ero, "\0");
	return (ero);
}

/**
 * ero_in_cd - the error message for command cd in get_cd
 * @datash: the data relevance (directory)
 * Return: an error message
 */

char *ero_in_cd(data_shell *datash)
{
	int len, leng_ab;
	char *ero, *v_str, *mesg;

	v_str = a_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		mesg = ": Illegal option ";
		leng_ab = 2;
	}
	else
	{
		mesg = ": can't cd to ";
		leng_ab = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(v_str) + _strlen(mesg) + leng_ab + 5;
	ero = malloc(sizeof(char) * (len + 1));

	if (ero == 0)
	{
		free(v_str);
		return (NULL);
	}

	ero = concate_cd(datash, mesg, ero, v_str);

	free(v_str);

	return (ero);
}


/**
 * ero_not_found - the generic error message for command not found
 * @datash: the data operations
 * Return: an error message
 */

char *ero_not_found(data_shell *datash)
{
	int len;
	char *ero, *v_str;

	v_str = a_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(v_str);
	len += _strlen(datash->args[0]) + 16;
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
	_strcat(ero, ": not found\n");
	_strcat(ero, "\0");
	free(v_str);
	return (ero);
}
