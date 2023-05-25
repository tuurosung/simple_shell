#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((unused)) **front);
int shellby_help(char **args, char __attribute__((unused)) **front);

int (*get_builtin(char *command))(char **args, char **front)
{
        builtin_t funcs[] = {
                { "exit", shellby_exit },
                { "env", shellby_env },
                { "setenv", shellby_setenv },
                { "unsetenv", shellby_unsetenv},
                { "cd", shellby_cd },
                { "alias", shellby_alias },
                { "help", shellby_help },
                { NULL, NULL }

        };
        int i;

        for (i = 0; funcs[i].name; i++)
        {
                if (_strcmp(funcs[i].name, command) == 0)
                        break;
        }
        return (funcs[i].f);
}

int shellby_exit(char **args, char **front)
{
        int i, int_len = 10;
        unsigned int number = 0, max = 1 << (sizeof(int) * 8 - 1);

        if (args[0])
        {
                if (args[0][0] == '+')
                {
                        i = 1;
                        int_len++;
                }

                for (; args[0][i] ; i++)
                {
                        if (i <= int_len && args[0][i] >= '0' && args[0][i] <= '9')
                                number = (number * 10) + (args[0][i] - '0');
                        else 
                                return (create_error(--args, 2));
                }
        }
        else 
        {
                return (-3);
        }
        if (number > max - 1)
                return (create_error(--args, 2));
        
        args -= 1;
        free_args(args, front);
        free_env();
        free_alias_list(aliases);
        exit(number);
}

int shellby_cd(char **args, char __attribute__((unused)) **front)
{
        char **dir_info, *new_line = "\n";
        char *prev_pwd = NULL, *pwd = NULL;
        struct stat dir;

        prev_pwd = getcwd(prev_pwd, 0);
        if (!prev_pwd) 
                return (-1);

        if (args[0])
        {
                if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
                {
                        if ((args[0][1] == '-' && args[0][2] == '\0') ||
                            args[0][1] == '\0')
                        {
                                if (_getenv("prev_pwd") != NULL)
                                        (chdir(*_getenv("prev_pwd") + 7));
                        }
                        else
                        {
                                free(prev_pwd);
                                return (create_error(args, 2));
                        }
                }
                else
                {
                        if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) && ((dir.st_mode & S_IXUSR) != 0))
                                chdir(args[0]);
                        else
                        {
                                free(prev_pwd);
                                return (create_error(args, 2));
                        }
                }
        }
        else
        {
                if (_getenv("HOME") != NULL)
                        chdir(*(_getenv("HOME")) + 5);
        }

        pwd = getcwd(pwd, 0);
        if (!pwd)
                return (-1);

        dir_info = malloc(sizeof(char *) * 2);
        if (!dir_info)
                return (-1);

        dir_info[0] = "prev_pwd";
        dir_info[1] = prev_pwd;
        if (shellby_setenv(dir_info, dir_info) == -1)
                return (-1);

        dir_info[0] = "PWD";
        dir_info[1] = pwd;
        if (shellby_setenv(dir_info, dir_info) == -1)
                return (-1);
        if (args[0] && args[0][0] == '-' && args[0][1] != '-')
        {
                write(STDOUT_FILENO, pwd, _strlen(pwd));
                write(STDOUT_FILENO, new_line, 1);
        }
        free(prev_pwd);
        free(pwd);
        free(dir_info);
        return (0);
}

int shellby_help(char **args, char __attribute__((unused)) **front)
{
        if (!args[0])
                help_all();
        else if (_strcmp(args[0], "alias") == 0)
                help_alias();
        else if (_strcmp(args[0], "cd") == 0)
                help_cd();
        else if (_strcmp(args[0], "exit") == 0)
                help_exit();
        else if (_strcmp(args[0], "env") == 0)
                help_env();
        else if (_strcmp(args[0], "setenv") == 0)
                help_setenv();
        else if (_strcmp(args[0], "unsetenv") == 0)
                help_unsetenv();
        else if (_strcmp(args[0], "help") == 0)
                help_help();
        else
                write(STDERR_FILENO, name, _strlen(name));
        return (0);
}