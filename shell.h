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

typedef struct list_s
{

} list_t

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




#endif
