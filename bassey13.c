#include "cat.h"

/**
 * cd_shell_p - changes current directory
 *
 * @datash_p: data relevant
 * Return: 1 on success
 */
int cd_shell_p(data_shell_p *datash_p)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash_p->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp_p("$HOME", dir);
		ishome2 = _strcmp_p("~", dir);
		isddash = _strcmp_p("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home_p(datash_p);
		return (1);
	}

	if (_strcmp_p("-", dir) == 0)
	{
		cd_previous_p(datash_p);
		return (1);
	}

	if (_strcmp_p(".", dir) == 0 || _strcmp_p("..", dir) == 0)
	{
		cd_dot_p(datash_p);
		return (1);
	}

	cd_to_p(datash_p);

	return (1);
}
