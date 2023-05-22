#ifndef SHELL_H
#define SHELL_H

<<<<<<< HEAD
=======
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
>>>>>>> 775e69680ee0ca5f8749807d646ce5fbdf1b287c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
<<<<<<< HEAD
#include <sys/wait.h>
#include <sys/stat.h>
=======
>>>>>>> 775e69680ee0ca5f8749807d646ce5fbdf1b287c


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
