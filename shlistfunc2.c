#include "bshell.h"

/**
 * free_rvar_list - this frees a r_var list
 * @head: the linked list head
 * Return: no return
 */

void free_rvar_list(r_var **head)
{
	r_var *tmp, *cr;

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
 * add_rvar_node - this adds a variable at the end
 * of a r_var list.
 * @val: variable value.
 * @head: the head of linked list involved
 * @lvar: variable length involved
 * @lval: value length involved
 * Return: the address head.
 */

r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *nw, *tmp;

	nw = malloc(sizeof(r_var));
	if (nw == NULL)
		return (NULL);

	nw->len_var = lvar;
	nw->val = val;
	nw->len_val = lval;

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
