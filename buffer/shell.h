#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

typedef struct glob_info
{
    char *name;
    char *hist;
} info_t;

/* define constants */
#define END_OF_FILE -2
#define EXIT -3

/* define buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* CMD CHAINS*/
#define CMD_CHAIN 3
#define CMD_AND   2
#define CMD_OR 1
#define CMD_NORM 0

extern char **environ;

#define TO_LOWER 1
#define TO_UNSIGNED 2

/**
 * struct builtin - a struct that defines builtin function;
 * @name: the name of the function
 * @f: the address of the function
 */

typedef struct builtin_s
{
    char *name;
    int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - a struct that defines a linked list.
 * @dir: a working directory/ path.
 * @next: the address of another linked list element.
*/

typedef struct list_s
{
    char *dir;
    struct list_s *next;
} list_t;

typedef struct alias_s
{
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

alias_t *aliases;

/* variables */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* string protype functions  defined in file (string_prototypes.c)*/
int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t i);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *terminus);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* string prototype functions defined in file (string_prototypes2.c) */
char *_strchr(char *str, char c);
int _strspn(char *str, char *match);
int _strcmp(char* str1, char* str2);
int _strncmp(const char *str1, const char *str2, size_t len);

/* error handling functions */
int create_error(char **args, int error_code);
// char *error_env(char **args, );
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);


alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_node_list(list_t *head);


void free_args(char **args, char **front);
char *_itoa(int number);
int handle_args(int *ret_var);

/* functions from file - handle_inputs */
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);



int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) * *front);
int shellby_setenv(char **args, char __attribute__((__unused__)) * *front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) * *front);
int shellby_cd(char **args, char __attribute__((__unused__)) * *front);
int shellby_alias(char **args, char __attribute__((__unused__)) * *front);
int shellby_help(char **args, char __attribute__((__unused__)) * *front);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *filepath, int *ret_var);

#endif
