#include "cat.h"

/**
 * get_error_p - calls the error according the builtin, syntax or permission
 * @datash_p: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error_p(data_shell_p *datash_p, int eval)
{
	char *error;

	switch (eval)
	{
		case -1:
			error = error_env_p(datash_p);
			break;
		case 126:
			error = error_path_126_p(datash_p);
			break;
		case 127:
			error = error_not_found_p(datash_p);
			break;
		case 2:
			if (_strcmp_p("exit", datash_p->args[0]) == 0)
				error = error_exit_shell_p(datash_p);
			else if (_strcmp_p("cd", datash_p->args[0]) == 0)
				error = error_get_cd_p(datash_p);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen_p(error));
		free(error);
	}

	datash_p->status = eval;
	return (eval);
}
