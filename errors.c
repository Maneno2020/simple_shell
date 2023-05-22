#include "shell.h"

/**
 * _eputs - displays input string
 * @str: string to print
 *
 * Return: nothing
 */
void _eputs(char *str)
{
	int i = 0;


	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}


/**
 * _eputchar - to write the char c to stderr
 * @c: char to be printed
 *
 * Return: if true 1.
 * If false, -1 is returned and errno is appropriately set.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
	write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	buf[i++] = c;
	return (1);
}

/**
 * _putfd - to write char c to given fd
 * @c: char to be printed
 * @fd: filedescriptor to be written to
 *
 * Return: 1 if true.
 * Otherwise, -1 is returned, and errno is appropriately set.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
	write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - displays the input string
 * @str: String to print
 * @fd: filedescriptor to be written to
 *
 * Return: number of characters put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
