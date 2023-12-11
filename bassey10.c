#include "cat.h"

/**
 * rev_string_p - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string_p(char *s)
{
	int count = 0, i, j2;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j2 = i + 1; j2 > 0; j2--)
		{
			temp = *(str + j2);
			*(str + j2) = *(str + (j2 - 1));
			*(str + (j2 - 1)) = temp;
		}
	}
}
