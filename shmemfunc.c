#include "bshell.h"

/**
 * _reallocab - this reallocates memory block of double pointer.
 * @pt: double pointer to the memory previously allocated.
 * @now_size: the new size in bytes of new memory block.
 * @past_size: the size in bytes of allocated space of ptr.
 * Return: pt
 * if the now_size == past_size, then returns ptr without changes.
 * if malloc fails, returns NULL.
 */

char **_reallocab(char **pt, unsigned int past_size, unsigned int now_size)
{
	char **npt;
	unsigned int d;

	if (pt == NULL)
		return (malloc(sizeof(char *) * now_size));

	if (now_size == past_size)
		return (pt);

	npt = malloc(sizeof(char *) * now_size);
	if (npt == NULL)
		return (NULL);

	for (d = 0; d < past_size; d++)
		npt[d] = pt[d];

	free(pt);

	return (npt);
}

/**
 * _memcpy - this copies information between void pointers.
 * @npt: the destination pointer.
 * @size: the size of new pointer.
 * @pt: the source pointer.
 * Return: no return.
 */

void _memcpy(void *npt, const void *pt, unsigned int size)
{
	char *char_pt = (char *)pt;
	char *char_npt = (char *)npt;
	unsigned int d;

	for (d = 0; d < size; d++)
	char_npt[d] = char_pt[d];
}

/**
 * _realloc - this reallocates a memory block.
 * @pt: pointer to previously memoryvallocated.
 * @now_size: new size, in bytes, of the new memory block.
 * @past_size: the size in bytes of allocated space of pt.
 * Return: pt
 * if the now_size == past_size, then returns ptr without changes.
 * if malloc fails, returns NULL.
 */

void *_realloc(void *pt, unsigned int past_size, unsigned int now_size)
{
	void *npt;

	if (pt == NULL)
		return (malloc(now_size));

	if (now_size == 0)
	{
		free(pt);
		return (NULL);
	}

	if (now_size == past_size)
		return (pt);

	npt = malloc(now_size);
	if (npt == NULL)
		return (NULL);

	if (now_size < past_size)
		_memcpy(npt, pt, now_size);
	else
		_memcpy(npt, pt, past_size);

	free(pt);
	return (npt);
}
