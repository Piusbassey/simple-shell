#include "cat.h"

/**
 * without_comment_p - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment_p(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc_p(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop_p - Loop of shell
 * @datash_p: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop_p(data_shell_p *datash_p)
{
	int loop, i_eof;
	char *input_p;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input_p = read_line_p(&i_eof);
		if (i_eof != -1)
		{
			input_p = without_comment_p(input_p);
			if (input_p == NULL)
				continue;

			if (check_syntax_error_p(datash_p, input_p) == 1)
			{
				datash_p->status = 2;
				free(input_p);
				continue;
			}
			input_p = rep_var_p(input_p, datash_p);
			loop = split_commands_p(datash_p, input_p);
			datash_p->counter_p += 1;
			free(input_p);
		}
		else
		{
			loop = 0;
			free(input_p);
		}
	}
}
