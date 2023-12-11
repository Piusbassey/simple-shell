#include "cat.h"

/**
 * error_env_p - error message for env in get_env.
 * @datash_p: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env_p(data_shell_p *datash_p)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa_p(datash_p->counter_p);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen_p(datash_p->av_p[0]) + _strlen_p(ver_str);
	length += _strlen_p(datash_p->args[0]) + _strlen_p(msg) + 4;
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
	_strcat_p(error, msg);
	_strcat_p(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126_p - error message for path and failure denied permission.
 * @datash_p: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126_p(data_shell_p *datash_p)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa_p(datash_p->counter_p);
	length = _strlen_p(datash_p->av_p[0]) + _strlen_p(ver_str);
	length += _strlen_p(datash_p->args[0]) + 24;
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
	_strcat_p(error, ": Permission not granted\n");
	_strcat_p(error, "\0");
	free(ver_str);
	return (error);
}
