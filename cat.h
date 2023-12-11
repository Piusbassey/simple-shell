#ifndef CAT_H
#define CAT_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define BUFSIZE_ 1024
#define TOK_BUFSIZES 128
#define TOK_DELIM_P " \t\r\n\a"

/* an array of pointer to strings called the "environment" */
extern char **environ;


/**
 * struct file - struct that contains all relevant files on runtime
 * @av_p: argument vector
 * @input_p: command line written by the user
 * @args_p: tokens of the command line
 * @status: last status of the shell
 * @counter_p: lines counter
 * @_environ_p: environment variable
 * @pid: process ID of the shell
 */
typedef struct file
{
	char **av_p;
	char *input_p;
	char **args;
	int status;
	int counter_p;
	char **_environ_p;
	char *pid;
} data_shell_p;

/**
 * struct sep_list_p - single linked list
 * @separator_p: ; | &
 * @next: next node
 */
typedef struct sep_list_p
{
	char separator_p;
	struct sep_list_p *next;
} sep_listp;

/**
 * struct line_list_p - single linked list
 * @line_p: command line
 * @next: next o store command lines
 */
typedef struct line_list_p
{
	char *line_p;
	struct line_list_p *next;
} line_list_p;

/**
 * struct r_var_list_p - single linked list
 * @len_var_p: length of the variable
 * @val_p: value of the variable
 * @len_val_p: length of the value
 * @next: next node
 */
typedef struct r_var_list_p
{
	int len_var_p;
	char *val_p;
	int len_val_p;
	struct r_var_list_p *next;
} r_var_p;

/**
 * struct builtin_p - Builtin struct for command args.
 * @name_p: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_p
{
	char *name_p;
	int (*f)(data_shell_p *datash_p);
} builtinp;

/* aux_lists.c */
sep_listp *add_sep_node_end_p(sep_listp **head, char sep);
void free_sep_list_p(sep_listp **head);
line_list_p *add_line_node_end_p(line_list_p **head, char *line);
void free_line_list_p(line_list_p **head);

/* aux_lists2.c */
r_var_p *add_rvar_node_p(r_var_p **head, int lvar, char *var, int lval);
void free_rvar_list_p(r_var_p **head);

/* aux_str functions */
char *_strcat_p(char *dest_p, const char *src_p);
char *_strcpy_p(char *dest_p, char *src_p);
int _strcmp_p(char *s1_p, char *s2_p);
char *_strchr_p(char *s, char c);
int _strspn_p(char *s, char *accept_p);

/* aux_mem.c */
void _memcpy_p(void *newptr, const void *ptr, unsigned int size);
void *_realloc_p(void *ptr, unsigned int old_size_p, unsigned int new_size_p);
char **_reallocdp_p(char **ptr, unsigned int old_size_p, unsigned int new_size_p);

/* aux_str2.c */
char *_strdup_p(const char *s);
int _strlen_p(const char *s);
int cmp_chars_p(char str[], const char *delim_p);
char *_strtok_p(char str[], const char *delim_p);
int _isdigit_p(const char *s);

/* aux_str3.c */
void rev_string_p(char *s);

/* check_syntax_error.c */
int repeated_char_p(char *input_p, int i);
int error_sep_op_p(char *input_p, int i, char last);
int first_char_p(char *input_p, int *i);
void print_syntax_error_p(data_shell_p *datash_p, char *input_p, int i, int bool);
int check_syntax_error_p(data_shell_p *datash_p, char *input_p);

/* shell_loop.c */
char *without_comment_p(char *in);
void shell_loop_p(data_shell_p *datash_p);

/* read_line.c */
char *read_line_p(int *i_eof);

/* split.c */
char *swap_char_p(char *input_p, int bool);
void add_nodes_p(sep_listp **head_s, line_list_p **head_l, char *input_p);
void go_next_p(sep_listp **list_s, line_list_p **list_l, data_shell_p *datash_p);
int split_commands_p(data_shell_p *datash_p, char *input_p);
char **split_line_p(char *input_p);

/* rep_var.c */
void check_env_p(r_var_p **h, char *in, data_shell_p *file);
int check_vars_p(r_var_p **h, char *in, char *st, data_shell_p *file);
char *replaced_input_p(r_var_p **head, char *input_p, char *new_input, int nlen);
char *rep_var_p(char *input_p, data_shell_p *datash_p);

/* get_line.c */
void bring_line_p(char **lineptr_p, size_t *n, char *buffer_p, size_t j);
ssize_t get_line_p(char **lineptr_p, size_t *n, FILE *stream_p);

/* exec_line */
int exec_line_p(data_shell_p *datash_p);

/* cmd_exec.c */
int is_cdir_p(char *path, int *i);
char *_which_p(char *cmd, char **_environ_p);
int is_executable_p(data_shell_p *datash_p);
int check_error_cmd_p(char *dir, data_shell_p *datash_p);
int cmd_exec_p(data_shell_p *datash_p);

/* env1.c */
char *_getenv_p(const char *name, char **_environ_p);
int _env_p(data_shell_p *datash_p);

/* env2.c */
char *copy_info_p(char *name, char *value);
void set_env_p(char *name, char *value, data_shell_p *datash_p);
int _setenv_p(data_shell_p *datash_p);
int _unsetenv_p(data_shell_p *datash_p);

/* cd.c */
void cd_dot_p(data_shell_p *datash_p);
void cd_to_p(data_shell_p *datash_p);
void cd_previous_p(data_shell_p *datash_p);
void cd_to_home_p(data_shell_p *datash_p);

/* cd_shell.c */
int cd_shell_p(data_shell_p *datash_p);

/* get_builtin */
int (*get_builtin_p(char *cmd))(data_shell_p *datash_p);

/* _exit.c */
int exit_shell_p(data_shell_p *datash_p);
/* aux_stdlib.c */
int get_len_p(int n);
char *aux_itoa_p(int n);
int _atoi_p(char *s);

/* aux_error1.c */
char *strcat_cd_p(data_shell_p *, char *, char *, char *);
char *error_get_cd_p(data_shell_p *datash_p);
char *error_not_found_p(data_shell_p *datash_p);
char *error_exit_shell_p(data_shell_p *datash_p);

/* aux_error2.c */
char *error_get_alias_p(char **args);
char *error_env_p(data_shell_p *datash_p);
char *error_syntax_p(char **args);
char *error_permission_p(char **args);
char *error_path_126_p(data_shell_p *datash_p);


/* get_error.c */
int get_error_p(data_shell_p *datash_p, int eval);

/* get_sigint.c */
void get_sigint_p(int sig);

/* aux_help.c */
void aux_help_env_p(void);
void aux_help_setenv_p(void);
void aux_help_unsetenv_p(void);
void aux_help_general_p(void);
void aux_help_exit_p(void);

/* aux_help2.c */
void aux_help_p(void);
void aux_help_alias_p(void);
void aux_help_cd_p(void);

/* get_help.c */
int get_help_p(data_shell_p *datash_p);

#endif
