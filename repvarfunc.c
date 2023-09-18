#include "bshell.h"

/**
 * search_env - this func checks if the typed variable is an env variable
 * @h: linked list head
 * @se: the input string involved
 * @data: data operation
 * Return: nothing
 */

void search_env(r_var **h, char *se, data_shell *data)
{
	int b, cir, chr, leval;
	char **_envron;

	_envron = data->_environ;
	for (cir = 0; _envron[cir]; cir++)
	{
		for (b = 1, chr = 0; _envron[cir][chr]; chr++)
		{
			if (_envron[cir][chr] == '=')
			{
				leval = _strlen(_envron[cir] + chr + 1);
				add_rvar_node(h, b, _envron[cir] + chr + 1, leval);
				return;
			}

			if (se[b] == _envron[cir][chr])
				b++;
			else
				break;
		}
	}

	for (b = 0; se[b]; b++)
	{
		if (se[b] == ' ' || se[b] == '\t' || se[b] == ';' || se[b] == '\n')
			break;
	}

	add_rvar_node(h, b, NULL, 0);
}

/**
 * search_vars - this func checkes the typed variable is $$ or $?
 * @h: linked list head
 * @se: the input string involved
 * @st: status of Shell
 * @data: the data operation
 * Return: nothing
 */

int search_vars(r_var **h, char *se, char *st, data_shell *data)
{
	int d, lns, lcd;

	lns = _strlen(st);
	lcd = _strlen(data->pid);

	for (d = 0; se[d]; d++)
	{
		if (se[d] == '$')
		{
			if (se[d + 1] == '?')
				add_rvar_node(h, 2, st, lns), d++;
			else if (se[d + 1] == '$')
				add_rvar_node(h, 2, data->pid, lcd), d++;
			else if (se[d + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (se[d + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (se[d + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (se[d + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (se[d + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				search_env(h, se + d, data);
		}
	}

	return (d);
}

/**
 * change_input - this funct replaces string into variables
 * @head: linked list head
 * @nleng: the new length involved
 * @input: the input string involved
 * @nw_input: the new input string involved
 * Return: the replaced string
 */

char *change_input(r_var **head, char *input, char *nw_input, int nleng)
{
	r_var *indx;
	int d, b, g;

	indx = *head;
	for (b = d = 0; d < nleng; d++)
	{
		if (input[b] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				nw_input[d] = input[b];
				b++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (g = 0; g < indx->len_var; g++)
					b++;
				d--;
			}
			else
			{
				for (g = 0; g < indx->len_val; g++)
				{
					nw_input[d] = indx->val[g];
					d++;
				}
				b += (indx->len_var);
				d--;
			}
			indx = indx->next;
		}
		else
		{
			nw_input[d] = input[b];
			b++;
		}
	}

	return (nw_input);
}

/**
 * rep_var - this functions call others to replace string into vars
 * @input: the input string involved
 * @datash: the data operation
 * Return: the replaced string involved
 */

char *rep_var(char *input, data_shell *datash)
{
	int oleng, nleng;
	r_var *head, *indx;
	char *status, *nw_input;

	status = a_itoa(datash->status);
	head = NULL;

	oleng = search_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nleng = 0;

	while (indx != NULL)
	{
		nleng += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nleng += oleng;

	nw_input = malloc(sizeof(char) * (nleng + 1));
	nw_input[nleng] = '\0';

	nw_input = change_input(&head, input, nw_input, nleng);
	free(input);
	free(status);
	free_rvar_list(&head);

	return (nw_input);
}
