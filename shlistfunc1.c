 #include "bshell.h"

/**
 * free_sep_list - this frees a sep_list
 * @head: the head of the linked list used
 * Return: no return.
 */

void free_sep_list(sep_list **head)
{
	sep_list *tmp, *cr;

	if (head != NULL)
	{
		cr = *head;
		while ((tmp = cr) != NULL)
		{
			cr = cr->next;
			free(tmp);
		}
		*head = NULL;
	}
}


/**
 * add_sep_node_end - this adds a separator found at the end of sep_list.
 * @head: head of the linked list.
 * @sep: the separator(; | &).
 * Return: the address of the head.
 */

sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *nw;
	sep_list *tmp;

	nw = malloc(sizeof(sep_list));
	if (nw == NULL)
		return (NULL);

	nw->separator = sep;
	nw->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = nw;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nw;
	}

	return (*head);
}

/**
 * add_line_node_end - this func adds a command line at the end
 * of a line_list.
 * @line: the command line.
 * @head: the head of the linked list used
 * Return: the address of the head
 */

line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *nw;
	line_list *tmp;

	nw = malloc(sizeof(line_list));
	if (nw == NULL)
		return (NULL);

	nw->line = line;
	nw->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = nw;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nw;
	}

	return (*head);
}

/**
 * free_line_list - this frees a line_list
 * @head: ths head of the linked list used
 * Return: no return.
 */

void free_line_list(line_list **head)
{
	line_list *tmp, *cr;

	if (head != NULL)
	{
		cr = *head;
		while ((tmp = cr) != NULL)
		{
			cr = cr->next;
			free(tmp);
		}
		*head = NULL;
	}
}
