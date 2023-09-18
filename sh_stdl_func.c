#include "bshell.h"

/**
 * i_atoi - this converts a string to an integer.
 * @t: the input string.
 * Return: an integer.
 */

int i_atoi(char *t)
{
	unsigned int numb = 0, size = 0;
	unsigned int ev = 0, np = 1, l = 1, d;

	while (*(t + numb) != '\0')
	{
		if (size > 0 && (*(t + numb) < '0' || *(t + numb) > '9'))
			break;

		if (*(t + numb) == '-')
			np *= -1;

		if ((*(t + numb) >= '0') && (*(t + numb) <= '9'))
		{
			if (size > 0)
				l *= 10;
			size++;
		}
		numb++;
	}

	for (d = numb - size; d < numb; d++)
	{
		ev = ev + ((*(t + d) - 48) * l);
		l /= 10;
	}
	return (ev * np);
}

/**
 * get_leng - this get the lenght of a number.
 * @a: the int number type
 * Return: the lenght of a number.
 */

int get_leng(int a)
{
	int len = 1;
	unsigned int nums;

	if (a < 0)
	{
		len++;
		nums = a * -1;
	}
	else
	{
		nums = a;
	}
	while (nums > 9)
	{
		len++;
		nums = nums / 10;
	}

	return (len);
}

/**
 * a_itoa - this helps function converts int to string.
 * @a: the int number type
 * Return: the String.
 */

char *a_itoa(int a)
{
	int len = get_leng(a);
	unsigned int nums;
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (a < 0)
	{
		nums = a * -1;
		buffer[0] = '-';
	}
	else
	{
		nums = a;
	}

	len--;
	do {
		*(buffer + len) = (nums % 10) + '0';
		nums = nums / 10;
		len--;
	}
	while (nums > 0)
		;
	return (buffer);
}
