#include "cat.h"

/**
 * copy_info_p - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value_p: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info_p(char *name, char *value_p)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen_p(name);
	len_value = _strlen_p(value_p);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy_p(new, name);
	_strcat_p(new, "=");
	_strcat_p(new, value_p);
	_strcat_p(new, "\0");

	return (new);
}

/**
 * set_env_p - sets an environment variable
 *
 * @name: name of the environment variable
 * @value_p: value of the environment variable
 * @datash_p: data structure (environ)
 * Return: no return
 */
void set_env_p(char *name, char *value_p, data_shell_p *datash_p)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash_p->_environ_p[i]; i++)
	{
		var_env = _strdup_p(datash_p->_environ_p[i]);
		name_env = _strtok_p(var_env, "=");
		if (_strcmp_p(name_env, name) == 0)
		{
			free(datash_p->_environ_p[i]);
			datash_p->_environ_p[i] = copy_info_p(name_env, value_p);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash_p->_environ_p = _reallocdp_p(datash_p->_environ_p,
			i, sizeof(char *) * (i + 2));
	datash_p->_environ_p[i] = copy_info_p(name, value_p);
	datash_p->_environ_p[i + 1] = NULL;
}

/**
 * _setenv_p - compares env variables names
 * with the name passed.
 * @datash_p: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv_p(data_shell_p *datash_p)
{

	if (datash_p->args[1] == NULL || datash_p->args[2] == NULL)
	{
		get_error_p(datash_p, -1);
		return (1);
	}

	set_env_p(datash_p->args[1], datash_p->args[2], datash_p);

	return (1);
}

/**
 * _unsetenv_p - deletes a environment variable
 *
 * @datash_p: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv_p(data_shell_p *datash_p)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j2, z1;

	if (datash_p->args[1] == NULL)
	{
		get_error_p(datash_p, -1);
		return (1);
	}
	z1 = -1;
	for (i = 0; datash_p->_environ_p[i]; i++)
	{
		var_env = _strdup_p(datash_p->_environ_p[i]);
		name_env = _strtok_p(var_env, "=");
		if (_strcmp_p(name_env, datash_p->args[1]) == 0)
		{
			z1 = i;
		}
		free(var_env);
	}
	if (z1 == -1)
	{
		get_error_p(datash_p, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j2 = 0; datash_p->_environ_p[i]; i++)
	{
		if (i != z1)
		{
			realloc_environ[j2] = datash_p->_environ_p[i];
			j2++;
		}
	}
	realloc_environ[j2] = NULL;
	free(datash_p->_environ_p[z1]);
	free(datash_p->_environ_p);
	datash_p->_environ_p = realloc_environ;
	return (1);
}
