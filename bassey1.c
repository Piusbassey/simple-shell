#include "cat.h"

/**
 * strcat_cd_p - function that concatenates the message for cd error
 *
 * @datash_p: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd_p(data_shell_p *datash_p,
		char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy_p(error, datash_p->av_p[0]);
	_strcat_p(error, ": ");
	_strcat_p(error, ver_str);
	_strcat_p(error, ": ");
	_strcat_p(error, datash_p->args[0]);
	_strcat_p(error, msg);
	if (datash_p->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash_p->args[1][1];
		illegal_flag[2] = '\0';
		_strcat_p(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat_p(error, datash_p->args[1]);
	}

	_strcat_p(error, "\n");
	_strcat_p(error, "\0");
	return (error);
}

/**
 * error_get_cd_p - error message for cd command in get_cd
 * @datash_p: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd_p(data_shell_p *datash_p)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa_p(datash_p->counter_p);
	if (datash_p->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen_p(datash_p->args[1]);
	}

	length = _strlen_p(datash_p->av_p[0]) + _strlen_p(datash_p->args[0]);
	length += _strlen_p(ver_str) + _strlen_p(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd_p(datash_p, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found_p - generic error message for command not found
 * @datash_p: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found_p(data_shell_p *datash_p)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa_p(datash_p->counter_p);
	length = _strlen_p(datash_p->av_p[0]) + _strlen_p(ver_str);
	length += _strlen_p(datash_p->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy_p(error, datash_p->av_p[0]);
	_strcat_p(error, ": ");
	_strcat_p(error, ver_str);
	_strcat_p(error, ": ");
	_strcat_p(error, datash_p->args[0]);
	_strcat_p(error, ": not found\n");
	_strcat_p(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell_p - generic error message for exit in get_exit
 * @datash_p: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell_p(data_shell_p *datash_p)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa_p(datash_p->counter_p);
	length = _strlen_p(datash_p->av_p[0]) + _strlen_p(ver_str);
	length += _strlen_p(datash_p->args[0]) + _strlen_p(datash_p->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy_p(error, datash_p->av_p[0]);
	_strcat_p(error, ": ");
	_strcat_p(error, ver_str);
	_strcat_p(error, ": ");
	_strcat_p(error, datash_p->args[0]);
	_strcat_p(error, ": Illegal number: ");
	_strcat_p(error, datash_p->args[1]);
	_strcat_p(error, "\n\0");
	free(ver_str);

	return (error);
}
