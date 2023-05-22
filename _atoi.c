#include "shell.h"

/**
* interactive - print true if shell is in interactive mode
* @info: address of struct
*
* Return: 1 for interactive mode then 0 otherwise
*/
int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - Checks for a delimeter character
* @c: character to be checked
* @delim: delimeter string
* Return: 1 if true, 0 otherwise
*/
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}


/**
* _isalpha - Checks for the alphabetic character
* @c: character to be input
* Return: 1 if c is alphabetic, 0 non-alphatecit
*/


int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}


/**
* _atoi - for converting strings to int
* @s: string to convert
* Return: 0 if no integers in the string, else converted number
*/


int _atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;


for (i = 0; s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;


if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}


if (sign == -1)
output = -result;
else
output = result;


return (output);
}
