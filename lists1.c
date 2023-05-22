#include "shell.h"

/**
 * list_len - to determine len of linked list
 * @h: the ptr to the first node
 *
 * Return: the list size
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
	h = h->next;
	i++;
	}
	return (i);
}

/**
 * list_to_strings - prints an array of strings of list->str
 * @head: the reference to the first node
 *
 * Return: the array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
	str = malloc(_strlen(node->str) + 1);
	if (!str)
	{
		for (j = 0; j < i; j++)
		free(strs[j]);
		free(strs);
		return (NULL);
	}

	str = _strcpy(str, node->str);
	strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - returns all elements of list_t linked list
 * @h: the ptr to the first node
 *
 * Return: the list size
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - prints node with string that starts with prefix
 * @node: reference to the list head
 * @prefix: String to be matched
 * @c: next char after prefix to be matched
 *
 * Return: match node if true, null otherwise
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
		return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - fetches a node index
 * @head: ptr to the list head
 * @node: the ptr to the node
 *
 * Return: node index else -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
	if (head == node)
	return (i);
	head = head->next;
	i++;
}
	return (-1);
}
