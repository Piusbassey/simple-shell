#include "cat.h"

/**
 * get_sigint_p - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint_p(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\npromise_me_something ", 20);
}
