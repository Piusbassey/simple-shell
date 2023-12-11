#include "cat.h"

/**
 * read_line_p - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_line_p(int *i_eof)
{
	char *input_p = NULL;
	size_t bufsize = 0;

	*i_eof = get_line_p(&input_p, &bufsize, stdin);

	return (input_p);
}
