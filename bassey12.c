#include "cat.h"

/**
 * cd_dot_p - changes to the parent directory
 *
 * @datash_p: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot_p(data_shell_p *datash_p)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup_p(pwd);
	set_env_p("OLDPWD", cp_pwd, datash_p);
	dir = datash_p->args[1];
	if (_strcmp_p(".", dir) == 0)
	{
		set_env_p("PWD", cp_pwd, datash_p);
		free(cp_pwd);
		return;
	}
	if (_strcmp_p("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string_p(cp_strtok_pwd);
	cp_strtok_pwd = _strtok_p(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok_p(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string_p(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env_p("PWD", cp_strtok_pwd, datash_p);
	}
	else
	{
		chdir("/");
		set_env_p("PWD", "/", datash_p);
	}
	datash_p->status = 0;
	free(cp_pwd);
}

/**
 * cd_to_p - changes to a directory given
 * by the user
 *
 * @datash_p: data relevant (directories)
 * Return: no return
 */
void cd_to_p(data_shell_p *datash_p)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash_p->args[1];
	if (chdir(dir) == -1)
	{
		get_error_p(datash_p, 2);
		return;
	}

	cp_pwd = _strdup_p(pwd);
	set_env_p("OLDPWD", cp_pwd, datash_p);

	cp_dir = _strdup_p(dir);
	set_env_p("PWD", cp_dir, datash_p);

	free(cp_pwd);
	free(cp_dir);

	datash_p->status = 0;

	chdir(dir);
}

/**
 * cd_previous_p - changes to the previous directory
 *
 * @datash_p: data relevant (environ)
 * Return: no return
 */
void cd_previous_p(data_shell_p *datash_p)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup_p(pwd);

	p_oldpwd = _getenv_p("OLDPWD", datash_p->_environ_p);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup_p(p_oldpwd);

	set_env_p("OLDPWD", cp_pwd, datash_p);

	if (chdir(cp_oldpwd) == -1)
		set_env_p("PWD", cp_pwd, datash_p);
	else
		set_env_p("PWD", cp_oldpwd, datash_p);

	p_pwd = _getenv_p("PWD", datash_p->_environ_p);

	write(STDOUT_FILENO, p_pwd, _strlen_p(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash_p->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home_p - changes to home directory
 *
 * @datash_p: data relevant (environ)
 * Return: no return
 */
void cd_to_home_p(data_shell_p *datash_p)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup_p(pwd);

	home = _getenv_p("HOME", datash_p->_environ_p);

	if (home == NULL)
	{
		set_env_p("OLDPWD", p_pwd, datash_p);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error_p(datash_p, 2);
		free(p_pwd);
		return;
	}

	set_env_p("OLDPWD", p_pwd, datash_p);
	set_env_p("PWD", home, datash_p);
	free(p_pwd);
	datash_p->status = 0;
}
