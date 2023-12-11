#include "cat.h"

/**
 * get_help_p - function that retrieves help messages according builtin
 * @datash_p: data structure (args and input)
 * Return: Return 0
 */
int get_help_p(data_shell_p *datash_p)
{

	if (datash_p->args[1] == 0)
		aux_help_general_p();
	else if (_strcmp_p(datash_p->args[1], "setenv") == 0)
		aux_help_setenv_p();
	else if (_strcmp_p(datash_p->args[1], "env") == 0)
		aux_help_env_p();
	else if (_strcmp_p(datash_p->args[1], "unsetenv") == 0)
		aux_help_unsetenv_p();
	else if (_strcmp_p(datash_p->args[1], "help") == 0)
		aux_help_p();
	else if (_strcmp_p(datash_p->args[1], "exit") == 0)
		aux_help_exit_p();
	else if (_strcmp_p(datash_p->args[1], "cd") == 0)
		aux_help_cd_p();
	else if (_strcmp_p(datash_p->args[1], "alias") == 0)
		aux_help_alias_p();
	else
		write(STDERR_FILENO, datash_p->args[0],
				_strlen_p(datash_p->args[0]));

	datash_p->status = 0;
	return (1);
}
