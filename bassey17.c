#include "cat.h"

/**
 * bring_line_p - assigns the line var for get_line
 * @lineptr_p: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j2: size of buffer
 */
void bring_line_p(char **lineptr_p, size_t *n, char *buffer, size_t j2)
{

	if (*lineptr_p == NULL)
	{
		if  (j2 > BUFSIZE_)
			*n = j2;

		else
			*n = BUFSIZE_;
		*lineptr_p = buffer;
	}
	else if (*n < j2)
	{
		if (j2 > BUFSIZE_)
			*n = j2;
		else
			*n = BUFSIZE_;
		*lineptr_p = buffer;
	}
	else
	{
		_strcpy_p(*lineptr_p, buffer);
		free(buffer);
	}
}
/**
 * get_line_p - Read inpt from stream
 * @lineptr_p: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line_p(char **lineptr_p, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input_p;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input_p == 0)
		fflush(stream);
	else
		return (-1);
	input_p = 0;

	buffer = malloc(sizeof(char) * BUFSIZE_);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input_p == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input_p != 0)
		{
			input_p++;
			break;
		}
		if (input_p >= BUFSIZE_)
			buffer = _realloc_p(buffer, input_p, input_p + 1);
		buffer[input_p] = t;
		input_p++;
	}
	buffer[input_p] = '\0';
	bring_line_p(lineptr_p, n, buffer, input_p);
	retval = input_p;
	if (i != 0)
		input_p = 0;
	return (retval);
}
