/**
 * aux_help_p - Help information for the builtin help.
 * Return: no return
 */
void aux_help_p(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "\tDisplay information about builtin cmds\n ";
	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "Displays brief summaries of builtin cmds.\n";
	write(STDOUT_FILENO, help, _strlen_p(help));
}
/**
 * aux_help_alias_p - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_alias_p(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen_p(help));
}
/**
 * aux_help_cd_p - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_cd_p(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen_p(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen_p(help));
}
