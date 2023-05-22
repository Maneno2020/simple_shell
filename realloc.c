#include "shell.h"

/**
 * _memset - for filling the memory with a constant byte
 * @s: ptr to memory area
 * @b: byte to be filled *s with
 * @n: amount of bytes to be filled
 * Return: (s) a reference to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - empties the string of strings
 * @pp: the string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
	return;
	while (*pp)
	free(*pp++);
	free(a);
}

/**
 * _realloc - to reallocate memory block
 * @ptr: pntr to the previous memory block allocated
 * @old_size: the size of byte of the previous block
 * @new_size: size of byte of new block
 *
 * Return: ptr to the da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	return (malloc(new_size));
	if (!new_size)
	return (free(ptr), NULL);
	if (new_size == old_size)
	return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
