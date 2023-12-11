#include "cat.h"

/**
 * get_builtin_p - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin_p(char *cmd))(data_shell_p *)
{
	builtinp builtin[] = {
		{ "env", _env_p },
		{ "exit", exit_shell_p },
		{ "setenv", _setenv_p },
		{ "unsetenv", _unsetenv_p},
		{ "cd", cd_shell_p },
		{ "help", get_help_p },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name_p; i++)
	{
		if (_strcmp_p(builtin[i].name_p, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
