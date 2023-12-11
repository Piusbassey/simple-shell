#include "cat.h"

/**
 * aux_help_env_p - Help information for the builtin env
 * Return: no return
 */
void aux_help_env_p(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen_p(help));

}
/**
 * aux_help_setenv_p - Help information for the builtin setenv
 * Return: no return
 */
void aux_help_setenv_p(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen_p(help));
}
/**
 * aux_help_unsetenv_p - Help information for the builtin unsetenv
 * Return: no return
 */
void aux_help_unsetenv_p(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen_p(help));
}


/**
 * aux_help_general_p - Entry point for help information for the help builtin
 * Return: no return
 */
void aux_help_general_p(void)
{
	char *help = "Promise bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen_p(help));
}
/**
 * aux_help_exit_p - Help information fot the builint exit
 * Return: no return
 */
void aux_help_exit_p(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "statusis that of the last command .exe\n";
	write(STDOUT_FILENO, help, _strlen_p(help));
}
