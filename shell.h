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
#include <errno.h>


/* define constants */
#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
char *name;
int hist;

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
char **__getenv(const char *var);

/* string protype functions  defined in file (string_prototypes.c)*/
int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t i);

/* string prototype functions defined in file (string_prototypes2.c) */
char *_strchr(char *str, char c);
int _strspn(char *str, char *match);
int _strcmp(char* str1, char* str2);
int _strncmp(const char *str1, const char *str2, size_t len);

/* error handling functions */
int create_error(char **args, int error_code);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);


alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t *head, char *dir);
void free_node_list(list_t *head);


void free_args(char **args, char **front);
char *_itoa(int number);
int handle_args(int *ret_var);

int proc_file_commands(char *filepath, int *ret_var);

#endif
