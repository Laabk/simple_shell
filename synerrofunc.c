#include "bshell.h"

/**
 * first_character - this func finds index of the first char
 * @input: the input string
 * @d: the index involved
 * Return: 1 for error. 0 in other case.
 */

int first_character(char *input, int *d)
{

	for (*d = 0; input[*d]; *d += 1)
	{
		if (input[*d] == ' ' || input[*d] == '\t')
			continue;

		if (input[*d] == ';' || input[*d] == '|' || input[*d] == '&')
			return (-1);

		break;
	}

	return (0);
}


/**
 * repeat_charact - this func counts the repetitions of a char
 * @input: the input string involved
 * @d: the index
 * Return: repetitions
 */

int repeat_charact(char *input, int d)
{
	if (*(input - 1) == *input)
	return (repeat_charact(input - 1, d + 1));
	return (d);
}

/**
 * ero_sep_op - this func finds syntax errors
 * @input: the input string
 * @d: the index involved
 * @last: the last char read
 * Return: index of error. 0 when there are no
 * errors
 */

int ero_sep_op(char *input, int d, char last)
{
	int numb;

	numb = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (ero_sep_op(input + 1, d + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (d);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (d);

		if (last == '|')
		{
			numb = repeat_charact(input, 0);
			if (numb == 0 || numb > 1)
				return (d);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (d);

		if (last == '&')
		{
			numb = repeat_charact(input, 0);
			if (numb == 0 || numb > 1)
				return (d);
		}
	}

	return (ero_sep_op(input + 1, d + 1, *input));
}

/**
 * print_syntaxero - this func prints when a syntax error is found
 * @datash: the data operation
 * @input: the input string involved
 * @d: the error
 * @bool: the control message error
 * Return: nothing
 */

void print_syntaxero(data_shell *datash, char *input, int d, int bool)
{
	char *mesg, *mesg2, *mesg3, *ero, *counter;
	int len;

	if (input[d] == ';')
	{
		if (bool == 0)
			mesg = (input[d + 1] == ';' ? ";;" : ";");
		else
			mesg = (input[d - 1] == ';' ? ";;" : ";");
	}

	if (input[d] == '|')
		mesg = (input[d + 1] == '|' ? "||" : "|");

	if (input[d] == '&')
		mesg = (input[d + 1] == '&' ? "&&" : "&");

	mesg2 = ": Syntax error: \"";
	mesg3 = "\" unexpected\n";
	counter = a_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(counter);
	len += _strlen(mesg) + _strlen(mesg2) + _strlen(mesg3) + 2;

	ero = malloc(sizeof(char) * (len + 1));
	if (ero == 0)
	{
		free(counter);
		return;
	}
	_strcpy(ero, datash->av[0]);
	_strcat(ero, ": ");
	_strcat(ero, counter);
	_strcat(ero, mesg2);
	_strcat(ero, mesg);
	_strcat(ero, mesg3);
	_strcat(ero, "\0");

	write(STDERR_FILENO, ero, len);
	free(ero);
	free(counter);
}

/**
 * check_syntaxero - this is an intermediate function to
 * find and print a errorsyntax
 * @datash: the data operation
 * @input: the input string involved
 * Return: 1 for an error. 0 in other case
 */

int check_syntaxero(data_shell *datash, char *input)
{
	int strt = 0;
	int b_charact = 0, d = 0;

	b_charact = first_character(input, &strt);
	if (b_charact == -1)
	{
		print_syntaxero(datash, input, strt, 0);
		return (1);
	}

	d = ero_sep_op(input + strt, 0, *(input + strt));
	if (d != 0)
	{
		print_syntaxero(datash, input, strt + d, 1);
		return (1);
	}

	return (0);
}
