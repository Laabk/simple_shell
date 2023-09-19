#include "bshell.h"

/**
 * _isdigit - thi funct defines if string passed is a number
 * @t: the input string
 * Return: 1 for string number. 0 in other case.
 */

int _isdigit(const char *t)
{
	unsigned int d;

	for (d = 0; t[d]; d++)
	{
		if (t[d] < 48 || t[d] > 57)
			return (0);
	}
	return (1);
}

/**
 * _strdup - this fubc duplicates a str in the heap memory.
 * @t: pointer str of the type char
 * Return: the duplicated str
 */
char *_strdup(const char *t)
{
	size_t leng;
	char *nw;

	leng = _strlen(t);
	nw = malloc(sizeof(char) * (leng + 1));
	if (nw == NULL)
		return (NULL);
	_memcpy(nw, t, leng + 1);
	return (nw);
}

/**
 * _strlen - this returns the lenght of a string.
 * @t: pointer of the type char
 * Return: Always 0.
 */

int _strlen(const char *t)
{
	int leng = 0;

	while (t[leng] != 0)
	{
	leng++;
	}
	return (leng);
}


/**
 * cmp_chars - this func compare chars of strings
 * @str: the input string.
 * @delim: the delimiter.
 * Return: 1 for equals, 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int d = 0, b = 0;
	unsigned int g = 0;

	while (str[d])
	{
		while (delim[b])
		{
			if (str[d] == delim[b])
			{
				g++;
				break;
			}
			b++;
		}
		d++;
	}
	if (d == g)
		return (1);
	return (0);
}

/**
 * _strtok - this func splits a string by some delimiter.
 * @str: the input string.
 * @delim: the delimiter used
 * Return: the split string
 */

char *_strtok(char str[], const char *delim)
{
	 unsigned int d, bool;
	static char *divd, *str_stp;
	char *str_bgin;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		divd = str;
		d = _strlen(str);
		str_stp = &str[d];
	}
	str_bgin = divd;
	if (str_bgin == str_stp)
		return (NULL);

	for (bool = 0; *divd; divd++)
	{
		if (divd != str_bgin)
			if (*divd && *(divd - 1) == '\0')
				break;
		for (d = 0; delim[d]; d++)
		{
			if (*divd == delim[d])
			{
				*divd = '\0';
				if (divd == str_bgin)
					str_bgin++;
				break;
			}
		}
		if (bool == 0 && *divd)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_bgin);
}
