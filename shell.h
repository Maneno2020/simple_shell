#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

/* to read or write buffers */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

/* to chain command  */
#define CMD_NORM        0
#define CMD_OR                1
#define CMD_AND                2
#define CMD_CHAIN        3

/* to convert_number() */
#define CONVERT_LOWERCASE        1
#define CONVERT_UNSIGNED        2

/* 1 for using system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE        ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - Singly Linked List
 * @num: number field
 * @str: String
 * @next: For pointing to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * struct passinfo - with pseudo-arguements to pass into a function,
 * to allow uniform prototype for function ptr structure
 * @arg: String from getline with arguements
 * @argv:array of strings from arg
 * @path: path of string for current command
 * @argc: arg count
 * @line_count: error count
 * @err_num: exit() code for error
 * @linecount_flag: if true, count this line of input
 * @fname: filename of the program
 * @env: local copy of linked list of environ
 * @environ: the custom modified copy of environ from LL env
 * @history: History node
 * @alias: alias node
 * @env_changed: on if environ was modified
 * @status: print status of last executed command
 * @cmd_buf:  ptr address to the cmd_buf, on if chaining
 * @cmd_buf_type: the CMD_type ||, &&, ;
 * @readfd: fd where to read line input
 * @histcount: count for history line number
 */
typedef struct passinfo
{
	int argc;
	unsigned int line_count;
	int err_num;
	char *path;
	list_t *history;
	char *fname;
	list_t *env;
	char *arg;
	list_t *alias;
	char **environ;
	int linecount_flag;
	char **argv;
	int env_changed;
	int status;

	char **cmd_buf; /* reference to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0}


/**
 * struct builtin - with a builtin string & related function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;




/* the toem_shloop.c */
int find_builtin(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);
void find_cmd(info_t *);

/* the toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);


/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char);

/* the toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);


/* the toem_string1.c */
char *_strdup(const char *);
char *_strcpy(char *, char *);
int _putchar(char);
void _puts(char *);


/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);


/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);


/* the toem_realloc.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* the toem_memory.c */
int bfree(void **);

/* the toem_errors1.c */
int _erratoi(char *);
int print_d(int, int);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*the toem_builtin.c */
int _myexit(info_t *);
int _myhelp(info_t *);
int _mycd(info_t *);


/* the toem_atoi.c */
int interactive(info_t *);
int _isalpha(int);
int is_delim(char, char *);
int _atoi(char *);

/* the toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);


/*the toem_getline.c */
ssize_t get_input(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);


/* the toem_getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);


/* the toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);

/* the toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t print_list_str(const list_t *);

/* the toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int replace_string(char **, char *);
int replace_alias(info_t *);

/* the toem_getenv.c */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* the toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int read_history(info_t *info);


/* the toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);

#endif