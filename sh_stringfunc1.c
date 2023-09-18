#include "bshell.h"


/**
 * *_strcpy - this funct Copies the string pointed to by src.
 * @dest: pointer to the dest of the copied str
 * @src: the pointer to the source of str
 * Return: destination
 */

char *_strcpy(char *dest, char *src)
{

	size_t n = 0;

	while (src[n] != '\0')
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = '\0';

	return (dest);
}

/**
 * _strcat - this func concatenate two strings
 * @dest: pointer to the dest of the copied str
 * @src: the pointer to the source of str
 * Return: dest
 */

char *_strcat(char *dest, const char *src)
{
	int d, b;

	for (d = 0; dest[d] != '\0'; d++)
		;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[d] = src[b];
		d++;
	}

	dest[d] = '\0';
	return (dest);
}

/**
 * _strcmp - this function that compares two strings involved
 * @t1: the string compared
 * @t2: the string compared
 * Return: Always 0.
 */

int _strcmp(char *t1, char *t2)
{
	int d;

	for (d = 0; t1[d] == t2[d] && t1[d]; d++)
		;

	if (t1[d] > t2[d])
		return (1);
	if (t1[d] < t2[d])
		return (-1);
	return (0);
}

/**
 * _strchr - this funct locates a character in a string
 * @t: the string involved
 * @c: the character.
 * Return: pointer to first occurrence of the character c.
 */

char *_strchr(char *t, char c)
{
	unsigned int d = 0;

	for (; *(t + d) != '\0'; d++)
		if (*(t + d) == c)
			return (t + d);
	if (*(t + d) == c)
		return (t + d);
	return ('\0');
}

/**
 * _strspn - this funct gets the length of a prefix substring.
 * @t: the initial segment involved
 * @accept: the accepted bytes.
 * Return: the number of accepted bytes.
 */

int _strspn(char *t, char *accept)
{
	int d, b;
	int bool;

	for (d = 0; *(t + d) != '\0'; d++)
	{
		bool = 1;
		for (b = 0; *(accept + b) != '\0'; b++)
		{
			if (*(t + d) == *(accept + b))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (d);
}
