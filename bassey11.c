#include "cat.h"

/**
 * _strcat_p - concatenate two strings
 * @dest_p: char pointer the dest of the copied str
 * @src_p: const char pointer the source of str
 * Return: the dest
 */
char *_strcat_p(char *dest_p, const char *src_p)
{
	int i;
	int j2;

	for (i = 0; dest_p[i] != '\0'; i++)
		;

	for (j2 = 0; src_p[j2] != '\0'; j2++)
	{
		dest_p[i] = src_p[j2];
		i++;
	}

	dest_p[i] = '\0';
	return (dest_p);
}
/**
 * *_strcpy_p - Copies the string pointed to by src.
 * @dest_p: Type char pointer the dest of the copied str
 * @src_p: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy_p(char *dest_p, char *src_p)
{

	size_t a;

	for (a = 0; src_p[a] != '\0'; a++)
	{
		dest_p[a] = src_p[a];
	}
	dest_p[a] = '\0';

	return (dest_p);
}
/**
 * _strcmp_p - Function that compares two strings.
 * @s1_p: type str compared
 * @s2_p: type str compared
 * if malloc fails, returns NULL.
 * Return: Always 0.
 */
int _strcmp_p(char *s1_p, char *s2_p)
{
	int i;

	for (i = 0; s1_p[i] == s2_p[i] && s1_p[i]; i++)
		;

	if (s1_p[i] > s2_p[i])
		return (1);
	if (s1_p[i] < s2_p[i])
		return (-1);
	return (0);
}
/**
 * _strchr_p - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr_p(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn_p - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn_p(char *s, char *accept)
{
	int i, j2, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j2 = 0; *(accept + j2) != '\0'; j2++)
		{
			if (*(s + i) == *(accept + j2))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
