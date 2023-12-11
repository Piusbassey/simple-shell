#include "cat.h"

/**
 * cmp_env_name_p - it compares variables names
 * with the name passed.
 * @nenv: name  environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name_p(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv_p - get an environment variable
 * @name: name environment variable
 * @_environ_p: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv_p(const char *name, char **_environ_p)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ_p[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name_p(_environ_p[i], name);
		if (mov)
		{
			ptr_env = _environ_p[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env_p - prints the evironment variables
 *
 * @datash_p: data relevant.
 * Return: 1 on success.
 */
int _env_p(data_shell_p *datash_p)
{
	int i, j2;

	for (i = 0; datash_p->_environ_p[i]; i++)
	{

		for (j2 = 0; datash_p->_environ_p[i][j2]; j2++)
			;

		write(STDOUT_FILENO, datash_p->_environ_p[i], j2);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash_p->status = 0;

	return (1);
}
