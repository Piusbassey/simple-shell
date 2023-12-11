#include "cat.h"

/**
 * swap_char_p - swaps | and & for non-printed chars
 *
 * @input_p:input
 * @bool: type of swap
 * Return: swapped string
 */

char *swap_char_p(char *input_p, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input_p[i]; i++)
		{
			if (input_p[i] == '|')
			{
				if (input_p[i + 1] != '|')
					input_p[i] = 16;
				else
					i++;
			}

			if (input_p[i] == '&')
			{
				if (input_p[i + 1] != '&')
					input_p[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input_p[i]; i++)
		{
			input_p[i] = (input_p[i] == 16 ? '|' : input_p[i]);
			input_p[i] = (input_p[i] == 12 ? '&' : input_p[i]);
		}
	}
	return (input_p);
}

/**
 * add_nodes_p - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input_p: input string
 * Return: no return
 */
void add_nodes_p(sep_listp **head_s, line_list_p **head_l, char *input_p)
{
	int i;
	char *line_p;

	input_p = swap_char_p(input_p, 0);

	for (i = 0; input_p[i]; i++)
	{
		if (input_p[i] == ';')
			add_sep_node_end_p(head_s, input_p[i]);

		if (input_p[i] == '|' || input_p[i] == '&')
		{
			add_sep_node_end_p(head_s, input_p[i]);
			i++;
		}
	}

	line_p = _strtok_p(input_p, ";|&");
	do {
		line_p = swap_char_p(line_p, 1);
		add_line_node_end_p(head_l, line_p);
		line_p = _strtok_p(NULL, ";|&");
	} while (line_p != NULL);

}

/**
 * go_next_p - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash_p: data structure
 * Return: no return
 */
void go_next_p(sep_listp **list_s,
		line_list_p **list_l, data_shell_p *datash_p)
{
	int loop_sep;
	sep_listp *ls_s;
	line_list_p *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash_p->status == 0)
		{
			if (ls_s->separator_p == '&' || ls_s->separator_p == ';')
				loop_sep = 0;
			if (ls_s->separator_p == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator_p == '|' || ls_s->separator_p == ';')
				loop_sep = 0;
			if (ls_s->separator_p == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands_p - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash_p: data structure
 * @input_p: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands_p(data_shell_p *datash_p, char *input_p)
{

	sep_listp *head_s, *list_s;
	line_list_p *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes_p(&head_s, &head_l, input_p);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash_p->input_p = list_l->line_p;
		datash_p->args = split_line_p(datash_p->input_p);
		loop = exec_line_p(datash_p);
		free(datash_p->args);

		if (loop == 0)
			break;

		go_next_p(&list_s, &list_l, datash_p);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list_p(&head_s);
	free_line_list_p(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line_p - tokenizes the input string
 *
 * @input_p: input string.
 * Return: string splitted.
 */
char **split_line_p(char *input_p)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZES;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok_p(input_p, TOK_DELIM_P);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZES;
			tokens = _reallocdp_p(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok_p(NULL, TOK_DELIM_P);
		tokens[i] = token;
	}

	return (tokens);
}
