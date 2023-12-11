#include "cat.h"

/**
 * free_data_p - frees data structure
 *
 * @datash_p: data structure
 * Return: no return
 */
void free_data_p(data_shell_p *datash_p)
{
	unsigned int i;

	for (i = 0; datash_p->_environ_p[i]; i++)
	{
		free(datash_p->_environ_p[i]);
	}

	free(datash_p->_environ_p);
	free(datash_p->pid);
}

/**
 * set_data_p - Initialize data structure
 *
 * @datash_p: data structure
 * @av_p: argument vector
 * Return: no return
 */
void set_data_p(data_shell_p *datash_p, char **av_p)
{
	unsigned int i;

	datash_p->av_p = av_p;
	datash_p->input_p = NULL;
	datash_p->args = NULL;
	datash_p->status = 0;
	datash_p->counter_p = 1;

	for (i = 0; environ[i]; i++)
		;

	datash_p->_environ_p = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash_p->_environ_p[i] = _strdup_p(environ[i]);
	}

	datash_p->_environ_p[i] = NULL;
	datash_p->pid = aux_itoa_p(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av_p: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av_p)
{
	data_shell_p datash_p;
	(void) ac;

	signal(SIGINT, get_sigint_p);
	set_data_p(&datash_p, av_p);
	shell_loop_p(&datash_p);
	free_data_p(&datash_p);
	if (datash_p.status < 0)
		return (255);
	return (datash_p.status);
}
