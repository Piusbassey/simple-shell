#include "cat.h"

/**
 * _memcpy_p - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy_p(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc_p - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size_p: size, in bytes, of the allocated space of ptr.
 * @new_size_p: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 */
void *_realloc_p(void *ptr, unsigned int old_size_p, unsigned int new_size_p)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size_p));

	if (new_size_p == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size_p == old_size_p)
		return (ptr);

	newptr = malloc(new_size_p);
	if (newptr == NULL)
		return (NULL);

	if (new_size_p < old_size_p)
		_memcpy_p(newptr, ptr, new_size_p);
	else
		_memcpy_p(newptr, ptr, old_size_p);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp_p - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size_p: size, in bytes, of the allocated space of ptr.
 * @new_size_p: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size_p == old_size, returns ptr without changes.
 */
char **_reallocdp_p(char **ptr, unsigned int old_size_p,
		unsigned int new_size_p)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size_p));

	if (new_size_p == old_size_p)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size_p);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size_p; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
