#include "shell.h"

/**
 * _strcpy - duplicates a string
 * @dest: Destination
 * @src: Source
 *
 * Return: Ptr to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - copies a string
 * @str: String to be copied
 *
 * Return: ptr to copied string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
	return (NULL);
	while (*str++)
	length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	return (NULL);
	for (length++; length--;)
	ret[length] = *--str;
	return (ret);
}

/**
 * _puts - returns an input string
 * @str: String to return
 *
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
	return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes char c to the stdout
 * @c: char to be printed
 *
 * Return: 1 on success.
 * Otherwise, -1 is returned, and errno is appropriately set.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	buf[i++] = c;
	return (1);
}
