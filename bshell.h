#ifndef _BSHELL_
#define _BSHELL_

#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* an array of pointers that shows strings called the "environment" */
extern char **environ;


/**
 * struct data - this contains all operation and relevant
 * data on the runtime
 * @args: the command line tokens used
 * @av: the argument vectors that are passed
 * @input: input commands in commandline byuser
 *
 * @status: this is the shell status
 * @counter: the lines counter present
 * @_environ: environment variable involved
 * @pid: the process ID of the shell used
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - a single linked list for the sepera.
 * @next: following node
 * @separator: ; | &
 * Description: container for the involved separators
 */

typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - a single linked list for the lines passed
 * @line: command line passed
 * @next: the node that follows next
 * Description: the container for the command lines
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - the single linked list for the rvar list
 * @len_var: length of the variable present
 * @next: node that follow next
 * @val: value of the variable present
 * @len_val: length value present
 *
 * Description: single linked list container for variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - the Builtin struct for the command args involved
 * @name: the command builtin name
 * @f: the data type function pointer
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

char *_strdup(const char *t);
int _strlen(const char *t);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *t);
void _memcpy(void *npt, const void *pt, unsigned int size);
void *_realloc(void *pt, unsigned int past_size, unsigned int now_size);
char **_reallocab(char **pt, unsigned int past_size, unsigned int now_size);
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *t1, char *t2);
char *_strchr(char *t, char c);
int cd_cddir(char *path, int *d);
char *func_which(char *cmd, char **_environ);
int func_execute(data_shell *datash);
int ero_cmd(char *dir, data_shell *datash);
int execute_cmd(data_shell *datash);
int _strspn(char *t, char *accept);
void reverse_string(char *t);
int repeat_charact(char *input, int d);
int ero_sep_op(char *input, int d, char last);
int first_character(char *input, int *d);
void print_syntaxero(data_shell *datash, char *input, int d, int bool);
int check_syntaxero(data_shell *datash, char *input);
char *_comment(char *se);
void _loops(data_shell *datash);
char *read_line(int *d_eag);
char *change_character(char *input, int bool);
void add_node(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int func_sort_commands(data_shell *datash, char *input);
char **func_sort_line(char *input);
void search_env(r_var **h, char *se, data_shell *data);
int search_vars(r_var **h, char *se, char *st, data_shell *data);
char *change_input(r_var **head, char *input, char *nw_input, int nleng);
char *rep_var(char *input, data_shell *datash);
void bring_line(char **linept, size_t *a, char *buffer, size_t b);
ssize_t get_line(char **linept, size_t *a, FILE *stream);
int execute_line(data_shell *datash);
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);
void cd_in(data_shell *datash);
void cd_go(data_shell *datash);
void cd_before(data_shell *datash);
void cd_home(data_shell *datash);
int cd_to_shell(data_shell *datash);
int (*get_builtin(char *cmd))(data_shell *datash);
int sh_exit(data_shell *datash);
int get_leng(int a);
char *a_itoa(int a);
int i_atoi(char *t);
char *concate_cd(data_shell *, char *, char *, char *);
char *ero_in_cd(data_shell *datash);
char *ero_not_found(data_shell *datash);
char *ero_sh_exit(data_shell *datash);
char *error_get_alias(char **args);
char *ero_env(data_shell *datash);
char *error_syntax(char **args);
char *ero_permission(char **args);
char *ero_path_126(data_shell *datash);
int in_ero(data_shell *datash, int eval);
void unsetenvihelps(void);
void generalhelps(void);
void exithelps(void);
void helps(void);
void aliashelps(void);
void cdhelps(void);
int sh_helps(data_shell *datash);
void _visio(int vis);
void envihelps(void);
void setenvihelps(void);

#endif
