#include "cat.h"


/**
 * _strdup_p - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup_p(const char *s)
{
	char *new;
	size_t len;

	len = _strlen_p(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy_p(new, s, len + 1);
	return (new);
}

/**
 * _strlen_p - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen_p(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars_p - compare chars of strings
 * @str: input string.
 * @delim_p: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars_p(char str[], const char *delim_p)
{
	unsigned int i, j2, z1;

	for (i = 0, z1 = 0; str[i]; i++)
	{
		for (j2 = 0; delim_p[j2]; j2++)
		{
			if (str[i] == delim_p[j2])
			{
				z1++;
				break;
			}
		}
	}
	if (i == z1)
		return (1);
	return (0);
}

/**
 * _strtok_p - splits a string by some delimiter.
 * @str: input string.
 * @delim_p: delimiter.
 *
 * Return: string splited.
 */
char *_strtok_p(char str[], const char *delim_p)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars_p(str, delim_p))
			return (NULL);
		splitted = str; /*Store first address*/
		i = _strlen_p(str);
		str_end = &str[i]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim_p[i]; i++)
		{
			if (*splitted == delim_p[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isdigit_p - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit_p(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
