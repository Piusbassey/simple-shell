#include "cat.h"

/**
 * get_len_p - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len_p(int n)
{
	unsigned int n1_p;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1_p = n * -1;
	}
	else
	{
		n1_p = n;
	}
	while (n1_p > 9)
	{
		lenght++;
		n1_p = n1_p / 10;
	}

	return (lenght);
}
/**
 * aux_itoa_p - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *aux_itoa_p(int n)
{
	unsigned int n1_p;
	int lenght = get_len_p(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		n1_p = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1_p = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n1_p % 10) + '0';
		n1_p = n1_p / 10;
		lenght--;
	}
	while (n1_p > 0)
		;
	return (buffer);
}

/**
 * _atoi_p - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi_p(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn_p = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn_p *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn_p);
}
