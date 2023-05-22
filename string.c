#include "shell.h"


/**
 * _strlen - prints len of string
 * @s: String whose len is to be checked
 *
 * Return: int len of the string
 */
int _strlen(char *s)
{
	int i = 0;


	if (!s)
		return (0);


	while (*s++)
		i++;
	return (i);
}


/**
 * _strcmp - makes lexicogarphic comparison of the two strings.
 * @s1: first string
 * @s2: second string
 *
 * Return: negative for s1 < s2, positive for s1 > s2, zero for s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * starts_with - identifies whether needle begin with haystack
 * @haystack: String to be searched
 * @needle: substring to search
 *
 * Return: reference of next character of the haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}


/**
 * _strcat - appends one string to the other
 * @dest: Destination buffer
 * @src: Source buffer
 *
 * Return: reference to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;


	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
