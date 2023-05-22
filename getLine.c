#include "shell.h"

/**
 * input_buf - Buffers chained commands
 * @info: parameter structure
 * @buf:  buffer address
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if buffer is empty, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
		if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* to eliminate trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) could this be a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - fetch a line minus newline
 * @info: parameter structure
 *
 * Return: bytes to be read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* ';'  buffer for Command chain */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	 _putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* commands still in chain buffer */
	{
		j = i; /* initialize new loop to current buf position */
		p = buf + i; /* fetch pointer to be returned */


		check_chain(info, buf, &j, i, len);
		while (j < len) /* loop to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}


		i = j + 1; /* incrementing past nulled ';'' */
		if (i >= len) /* the end of buffer? */
		{
			i = len = 0; /* Resetting position & length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass ptr back to the current command position*/
		return (_strlen(p)); /* print current command length*/
	}

	*buf_p = buf; /* if not chain then pass back buffer from _getline() */
	return (r); /* print of buffer length from _getline() */
}

/**
 * read_buf - inputs a buffer
 * @info: parameter structure
 * @buf: the buffer
 * @i: the size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;


	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - fetch next line of input from STDIN
 * @info: parameter structure
 * @ptr: pointer address to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if NOT NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;


	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;


	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);


	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);


	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);


	s += k - i;
	i = k;
	p = new_p;


	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - For blocking ctrl-C
 * @sig_num: Signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
