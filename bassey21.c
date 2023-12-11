#include "cat.h"

/**
 * exec_line_p - finds builtins and commands
 *
 * @datash_p: data relevant (args)
 * Return: 1 on success.
 */
int exec_line_p(data_shell_p *datash_p)
{
	int (*builtin)(data_shell_p *datash_p);

	if (datash_p->args[0] == NULL)
		return (1);

	builtin = get_builtin_p(datash_p->args[0]);

	if (builtin != NULL)
		return (builtin(datash_p));

	return (cmd_exec_p(datash_p));
}
