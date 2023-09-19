#include "bshell.h"

/**
 * read_line - this func reads the input string involved
 * @d_eag: the return value of getline function involved
 * Return: the input string involved
 */

char *read_line(int *d_eag)
{
	char *feed = NULL;
	size_t buffsz = 0;

	*d_eag = getline(&feed, &buffsz, stdin);

	return (feed);
}

/**
 * bring_line - this function assigns the line var for get_line
 * @linept: contain to store the input str
 * @buffer: the string in the  line
 * @a: the size of line ivolved
 * @b: the size of buffer involved
 */

void bring_line(char **linept, size_t *a, char *buffer, size_t b)
{

	if (*linept == NULL)
	{
		if  (b > BUFSIZE)
			*a = b;

		else
			*a = BUFSIZE;
		*linept = buffer;
	}
	else if (*a < b)
	{
		if (b > BUFSIZE)
			*a = b;
		else
			*a = BUFSIZE;
		*linept = buffer;
	}
	else
	{
		_strcpy(*linept, buffer);
		free(buffer);
	}
}

/**
 * get_line - this funct read inpt from stream
 * @linept: container that stores the input
 * @a: the size of lineptr involved
 * @stream: the stream to read in
 * Return: The bytes
 */

ssize_t get_line(char **linept, size_t *a, FILE *stream)
{
	int d;
	static ssize_t input;
	ssize_t sheval;
	char *conta, q = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	conta = malloc(sizeof(char) * BUFSIZE);
	if (conta == 0)
		return (-1);
	while (q != '\n')
	{
		d = read(STDIN_FILENO, &d, 1);
		if (d == -1 || (d == 0 && input == 0))
		{
			free(conta);
			return (-1);
		}
		if (d == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			conta = _realloc(conta, input, input + 1);
		conta[input] = q;
		input++;
	}
	conta[input] = '\0';
	bring_line(linept, a, conta, input);
	sheval = input;
	if (d != 0)
		input = 0;
	return (sheval);
}
