#include "shell.h"

/**
 * get_environ - Prints array of string copy of our environ
 * @info: structure with potential arguments to maintain
 * constant prototype of a function.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - eliminate env var
 * @info: structure with potential arguments to maintain
 *       constant prototype function.
 *  Return: 1 for delete else 0
 * @var: String environment variable property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
	p = starts_with(node->str, var);
		if (p && *p == '=')
	{
		info->env_changed = delete_node_at_index(&(info->env), i);
		i = 0;
			node = info->env;
			continue;
	}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Init a new env var,
 *         or change an existing env var
 * @info: structure with potential arguments to maintain
 *        constant prototype of a function.
 * @var: string environment variable property
 * @value: string environment variable value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
	p = starts_with(node->str, var);
	if (p && *p == '=')
	{
		free(node->str);
		node->str = buf;
		info->env_changed = 1;
		return (0);
	}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	return (0);
}
