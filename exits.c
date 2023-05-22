#include "shell.h"


/**
 **_strncpy - mimics a string
 *@dest: destination string to copy to
 *@src: source string
 *@n: number of chars to copy
 *Return: Concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - Combines two strings
 *@dest: first string
 *@src: second string
 *@n: maximum number of bytes used
 *Return: Concatenated String
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - searches a character in a string
 *@s: string to parse
 *@c: Character to be searched for
 *Return: (s) reference to memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');

	return (NULL);
}
