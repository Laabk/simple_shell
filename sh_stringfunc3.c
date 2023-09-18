#include "bshell.h"

/**
 * reverse_string - this reverses a string.
 * @t: the input string.
 * Return: no return.
 */

void reverse_string(char *t)
{
	int numb = 0;
	int d, b;
	char *stri;
	char tmp;

	while (numb >= 0)
	{
		if (t[numb] == '\0')
			break;
		numb++;
	}
	stri = t;

	for (d = 0; d < (numb - 1); d++)
	{
		for (b = d + 1; b > 0; b--)
		{
			tmp = *(stri + b);
			*(stri + b) = *(stri + (b - 1));
			*(stri + (b - 1)) = tmp;
		}
	}
}
