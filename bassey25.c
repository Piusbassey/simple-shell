#include "cat.h"

/**
 * check_env_p - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @file: data structure
 * Return: no return
 */
void check_env_p(r_var_p **h, char *in, data_shell_p *file)
{
	int row, chr, j2, lval;
	char **_envr;

	_envr = file->_environ_p;
	for (row = 0; _envr[row]; row++)
	{
		for (j2 = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen_p(_envr[row] + chr + 1);
				add_rvar_node_p(h, j2, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j2] == _envr[row][chr])
				j2++;
			else
				break;
		}
	}

	for (j2 = 0; in[j2]; j2++)
	{
		if (in[j2] == ' ' || in[j2] == '\t' || in[j2] == ';' || in[j2] == '\n')
			break;
	}

	add_rvar_node_p(h, j2, NULL, 0);
}

/**
 * check_vars_p - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @file: data structure
 * Return: no return
 */
int check_vars_p(r_var_p **h, char *in, char *st, data_shell_p *file)
{
	int i, lst, lpd;

	lst = _strlen_p(st);
	lpd = _strlen_p(file->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node_p(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_rvar_node_p(h, 2, file->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node_p(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node_p(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node_p(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node_p(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node_p(h, 0, NULL, 0);
			else
				check_env_p(h, in + i, file);
		}
	}

	return (i);
}

/**
 * replaced_input_p - replaces string into variables
 *
 * @head: head of the linked list
 * @input_p: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input_p(r_var_p **head,
		char *input_p, char *new_input, int nlen)
{
	r_var_p *indx;
	int i, j2, z1;

	indx = *head;
	for (j2 = i = 0; i < nlen; i++)
	{
		if (input_p[j2] == '$')
		{
			if (!(indx->len_var_p) && !(indx->len_val_p))
			{
				new_input[i] = input_p[j2];
				j2++;
			}
			else if (indx->len_var_p && !(indx->len_val_p))
			{
				for (z1 = 0; z1 < indx->len_var_p; z1++)
					j2++;
				i--;
			}
			else
			{
				for (z1 = 0; z1 < indx->len_val_p; z1++)
				{
					new_input[i] = indx->val_p[z1];
					i++;
				}
				j2 += (indx->len_var_p);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input_p[j2];
			j2++;
		}
	}

	return (new_input);
}

/**
 * rep_var_p - calls functions to replace string into vars
 *
 * @input_p: input string
 * @datash_p: data structure
 * Return: replaced string
 */
char *rep_var_p(char *input_p, data_shell_p *datash_p)
{
	r_var_p *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa_p(datash_p->status);
	head = NULL;

	olen = check_vars_p(&head, input_p, status, datash_p);

	if (head == NULL)
	{
		free(status);
		return (input_p);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val_p - indx->len_var_p);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input_p(&head, input_p, new_input, nlen);

	free(input_p);
	free(status);
	free_rvar_list_p(&head);

	return (new_input);
}
