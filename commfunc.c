#include "bshell.h"

/**
 * change_character - this func change | and & for all
 * non-printed character
 * @input: the input string involved
 * @bool:  pointer change of type
 * Return: the changed string involved
 */

char *change_character(char *input, int bool)
{
	int d;

	if (bool == 0)
	{
		for (d = 0; input[d]; d++)
		{
			if (input[d] == '|')
			{
				if (input[d + 1] != '|')
					input[d] = 16;
				else
					d++;
			}

			if (input[d] == '&')
			{
				if (input[d + 1] != '&')
					input[d] = 12;
				else
					d++;
			}
		}
	}
	else
	{
		for (d = 0; input[d]; d++)
		{
			input[d] = (input[d] == 16 ? '|' : input[d]);
			input[d] = (input[d] == 12 ? '&' : input[d]);
		}
	}
	return (input);
}

/**
 * add_node - gets more separators and the command lines
 * in the lists involved
 * @head_l: the command lines list head
 * @head_s: the separator list head
 * @input: the input string involved
 * Return: nothing
 *
 */

void add_node(sep_list **head_s, line_list **head_l, char *input)
{
	int d;
	char *lnet;

	input = change_character(input, 0);

	for (d = 0; input[d]; d++)
	{
		if (input[d] == ';')
			add_sep_node_end(head_s, input[d]);

		if (input[d] == '|' || input[d] == '&')
		{
			add_sep_node_end(head_s, input[d]);
			d++;
		}
	}

	lnet = _strtok(input, ";|&");
	do {
		lnet = change_character(lnet, 1);
		add_line_node_end(head_l, lnet);
		lnet = _strtok(NULL, ";|&");
	} while (lnet != NULL);

}

/**
 * go_next - this sets func to go the next command line stored
 * @reck_i: the command line list passed
 * @reck_o: separator list passed
 * @datash: data operation
 * Return: nothing
 */

void go_next(sep_list **reck_o, line_list **reck_i, data_shell *datash)
{
	int lope_sep;
	sep_list *vx_o;
	line_list *vx_i;

	lope_sep = 1;
	vx_o = *reck_o;
	vx_i = *reck_i;

	while (vx_o != NULL && lope_sep)
	{
		if (datash->status == 0)
		{
			if (vx_o->separator == '&' || vx_o->separator == ';')
				lope_sep = 0;
			if (vx_o->separator == '|')
				vx_i = vx_i->next, vx_o = vx_o->next;
		}
		else
		{
			if (vx_o->separator == '|' || vx_o->separator == ';')
				lope_sep = 0;
			if (vx_o->separator == '&')
				vx_i = vx_i->next, vx_o = vx_o->next;
		}
		if (vx_o != NULL && !lope_sep)
			vx_o = vx_o->next;
	}

	*reck_o = vx_o;
	*reck_i = vx_i;
}

/**
 * func_sort_commands - sorts the command lines according to
 * the separators ;, | and &,
 * @input: the input string involved
 * @datash: data operation
 * Return: 0 for an exit, 1 to continue
 */

int func_sort_commands(data_shell *datash, char *input)
{
	int lope;
	sep_list *head_s, *reck_o;
	line_list *head_l, *reck_i;

	head_s = NULL;
	head_l = NULL;

	add_node(&head_s, &head_l, input);

	reck_o = head_s;
	reck_i = head_l;

	while (reck_i != NULL)
	{
		datash->input = reck_i->line;
		datash->args = func_sort_line(datash->input);
		lope = execute_line(datash);
		free(datash->args);

		if (lope == 0)
			break;

		go_next(&reck_o, &reck_i, datash);

		if (reck_i != NULL)
			reck_i = reck_i->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (lope == 0)
		return (0);
	return (1);
}

/**
 * func_sort_line - sorts and tokenise the input string involved
 * @input: the input string involved
 * Return: the string sorted
 */

char **func_sort_line(char *input)
{
	size_t d;
	size_t busz;
	char **tkns, *tkn;

	busz = TOK_BUFSIZE;
	tkns = malloc(sizeof(char *) * (busz));
	if (tkns == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tkn = _strtok(input, TOK_DELIM);
	tkns[0] = tkn;

	for (d = 1; tkn != NULL; d++)
	{
		if (d == busz)
		{
			busz += TOK_BUFSIZE;
			tkns = _reallocab(tkns, d, sizeof(char *) * busz);
			if (tkns == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tkn = _strtok(NULL, TOK_DELIM);
		tkns[d] = tkn;
	}

	return (tkns);
}
