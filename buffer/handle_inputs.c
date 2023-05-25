#include "shell.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);


char *get_args(char *line, int *exe_ret)
{
        size_t n = 0;
        ssize_t read;
        char *prompt = "& ";

        if (line)
                free(line);
        
        read = _getline(&line, &n, STDIN_FILENO);
        if (read == 1)
                return (NULL);
        
        if (read == 1)
        {
                hist++;
                if (isatty(STDOUT_FILENO))
                        write(STDOUT_FILENO, prompt, 2);
                return (get_args(line, exe_ret));
        }

        line[read - 1] = '\0';
        variable_replacement(&line, exe_ret);
        handle_line(&line, read);

        return (line);
}

int call_args(char **args, char **front, int *exe_ret)
{
        int ret, i;

        if (!args[0])
                return (*exe_ret);
        
        for (i = 0; args[i]; i++)
        {
                if (_strncmp(args[i], "||", 2) == 0)
                {
                        free(args[i]);
                        args[i] = NULL;
                        args = replace_aliases(args);
                        ret = run_args(args, front, exe_ret);
                        if (*exe_ret != 0)
                        {
                                args = &args[++i];
                                i = 0;
                        }
                        else
                        {
                                for (i++; args[i]; i++)
                                        free(args[i]);
                                return (ret);
                        }
                }
                else if (_strncmp(args[i], "&&", 2) == 0)
                {
                        free(args[i]);
                        args[i] = NULL;
                        args = replace_aliases(args);
                        ret = run_args(args, front, exe_ret);
                        if (*exe_ret == 0)
                        {
                                args = &args[++i];
                                i = 0;
                        }
                        else
                        {
                                for (i++; args[i]; i++)
                                        free(args[i]);
                                return (ret);
                        }
                }
        }
        args = replace_aliases(args);
        ret = run_args(args, front, exe_ret);
        return (ret);        
}

int run_args(char **args, char **front, int *exe_ret)
{
        int ret, i;
        int (*builtin)(char **args, char **front);


        builtin = get_builtin(args[0]);

        if (builtin)
        {
                ret = builtin(args + 1, front);
                if (ret != EXIT)
                        *exe_ret = ret;

        }
        else
        {
                *exe_ret = execute(args, front);
                ret = *exe_ret;
        }

        hist++;

        for (i = 0; args[i] != NULL; i++)
                free(args[i]);
        return (ret);
}


int handle_args(int *exe_ret)
{
        int ret = 0, i;
        char **args, *line = NULL, **front;

        line = get_args(line, exe_ret);
        if (!line)
                return (END_OF_FILE);
        
        args = _strtok(line, " ");
        free(line);
        if (!args)
                return (ret);
        
        if (check_args(args) != 0)
        {
                *exe_ret = 2;
                free_args(args, args);
                return (*exe_ret);
        }

        front = args;

        for (i = 0; args[i]; i++)
        {
                if (_strncmp(args[i], ";", 1) == 0)
                {
                        free(args[i]);
                        args[i] = NULL;
                        ret = call_args(args, front, exe_ret);
                        args = &args[++i];
                        i = 0;
                }
        }

        if (args)
                ret = call_args(args, front, exe_ret);
        
        free(front);
        return (ret);
}

int check_args(char **args)
{
        size_t i;
        char *cur, *nex;

        for (i = 0; args[i]; i++)
        {
                cur = args[i];
                if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
                {
                        if (i == 0 || cur[1] ==';')
                                return (create_error(&args[i], 2));
                        nex = args[i + 1];
                        if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
                                return (create_error(&args[i + 1], 2));
                }
        }

        return (0);
}