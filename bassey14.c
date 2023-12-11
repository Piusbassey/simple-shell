#include "cat.h"

/**
 * repeated_char_p - counts the repetitions of a char
 *
 * @input_p: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char_p(char *input_p, int i)
{
	if (*(input_p - 1) == *input_p)
		return (repeated_char_p(input_p - 1, i + 1));

	return (i);
}

/**
 * error_sep_op_p - finds syntax errors
 *
 * @input_p: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op_p(char *input_p, int i, char last)
{
	int count;

	count = 0;
	if (*input_p == '\0')
		return (0);

	if (*input_p == ' ' || *input_p == '\t')
		return (error_sep_op_p(input_p + 1, i + 1, last));

	if (*input_p == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input_p == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char_p(input_p, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input_p == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_char_p(input_p, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op_p(input_p + 1, i + 1, *input_p));
}

/**
 * first_char_p - finds index of the first char
 *
 * @input_p: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char_p(char *input_p, int *i)
{

	for (*i = 0; input_p[*i]; *i += 1)
	{
		if (input_p[*i] == ' ' || input_p[*i] == '\t')
			continue;

		if (input_p[*i] == ';' || input_p[*i] == '|' || input_p[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error_p - prints when a syntax error is found
 *
 * @datash_p: data structure
 * @input_p: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error_p(data_shell_p *datash_p,
		char *input_p, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter_p;
	int length;

	if (input_p[i] == ';')
	{
		if (bool == 0)
			msg = (input_p[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input_p[i - 1] == ';' ? ";;" : ";");
	}

	if (input_p[i] == '|')
		msg = (input_p[i + 1] == '|' ? "||" : "|");

	if (input_p[i] == '&')
		msg = (input_p[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter_p = aux_itoa_p(datash_p->counter_p);
	length = _strlen_p(datash_p->av_p[0]) + _strlen_p(counter_p);
	length += _strlen_p(msg) + _strlen_p(msg2) + _strlen_p(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter_p);
		return;
	}
	_strcpy_p(error, datash_p->av_p[0]);
	_strcat_p(error, ": ");
	_strcat_p(error, counter_p);
	_strcat_p(error, msg2);
	_strcat_p(error, msg);
	_strcat_p(error, msg3);
	_strcat_p(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter_p);
}

/**
 * check_syntax_error_p - intermediate function to
 * find and print a syntax error
 *
 * @datash_p: data structure
 * @input_p: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error_p(data_shell_p *datash_p, char *input_p)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char_p(input_p, &begin);
	if (f_char == -1)
	{
		print_syntax_error_p(datash_p, input_p, begin, 0);
		return (1);
	}

	i = error_sep_op_p(input_p + begin, 0, *(input_p + begin));
	if (i != 0)
	{
		print_syntax_error_p(datash_p, input_p, begin + i, 1);
		return (1);
	}

	return (0);
}
