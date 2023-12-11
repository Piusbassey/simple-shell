#include "cat.h"

/**
 * is_cdir_p - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir_p(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which_p - locates a command
 *
 * @cmd: command name
 * @_environ_p: environment variable
 * Return: location of the command.
 */
char *_which_p(char *cmd, char **_environ_p)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv_p("PATH", _environ_p);
	if (path)
	{
		ptr_path = _strdup_p(path);
		len_cmd = _strlen_p(cmd);
		token_path = _strtok_p(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir_p(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen_p(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy_p(dir, token_path);
			_strcat_p(dir, "/");
			_strcat_p(dir, cmd);
			_strcat_p(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok_p(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable_p - determines if is an executable
 *
 * @datash_p: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable_p(data_shell_p *datash_p)
{
	struct stat st;
	int i;
	char *input_p;

	input_p = datash_p->args[0];
	for (i = 0; input_p[i]; i++)
	{
		if (input_p[i] == '.')
		{
			if (input_p[i + 1] == '.')
				return (0);
			if (input_p[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input_p[i] == '/' && i != 0)
		{
			if (input_p[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input_p + i, &st) == 0)
	{
		return (i);
	}
	get_error_p(datash_p, 127);
	return (-1);
}

/**
 * check_error_cmd_p - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @datash_p: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd_p(char *dir, data_shell_p *datash_p)
{
	if (dir == NULL)
	{
		get_error_p(datash_p, 127);
		return (1);
	}

	if (_strcmp_p(datash_p->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error_p(datash_p, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash_p->args[0], X_OK) == -1)
		{
			get_error_p(datash_p, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec_p - executes command lines
 *
 * @datash_p: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec_p(data_shell_p *datash_p)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable_p(datash_p);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which_p(datash_p->args[0], datash_p->_environ_p);
		if (check_error_cmd_p(dir, datash_p) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which_p(datash_p->args[0], datash_p->_environ_p);
		else
			dir = datash_p->args[0];
		execve(dir + exec, datash_p->args, datash_p->_environ_p);
	}
	else if (pd < 0)
	{
		perror(datash_p->av_p[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash_p->status = state / 256;
	return (1);
}
