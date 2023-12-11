#include "cat.h"

/**
 * exit_shell_p - exits the shell
 *
 * @datash_p: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell_p(data_shell_p *datash_p)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash_p->args[1] != NULL)
	{
		ustatus = _atoi_p(datash_p->args[1]);
		is_digit = _isdigit_p(datash_p->args[1]);
		str_len = _strlen_p(datash_p->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error_p(datash_p, 2);
			datash_p->status = 2;
			return (1);
		}
		datash_p->status = (ustatus % 256);
	}
	return (0);
}
