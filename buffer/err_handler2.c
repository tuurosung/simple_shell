#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);


char *error_126(char **args)
{
        char *error_msg, *hist_str;
        int len;

        hist_str = _itoa(hist);
        if (!hist_str)
                return (NULL);
        
        len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
        error_msg = malloc(sizeof(char) + (len + 1));

        if (!error_msg) 
        {
                free(hist_str);
                return (NULL);
        }

        _strcpy(error_msg, name);
        _strcat(error_msg, ": ");
        _strcat(error_msg, hist_str);
        _strcat(error_msg, ": ");
        _strcat(error_msg, args[0]);
        _strcat(error_msg, ": Sorry, you do not have enough permissions\n");

        free(hist_str);
        return (error_msg);

}


char *error_127(char **args)
{
        char *error_msg;
        char *hist_str;
        int len;

        hist_str = _itoa(hist);
        if (!hist_str)
                return (NULL);
        
        len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
        error_msg = malloc(sizeof(char) * (len + 1));

        if (!error_msg)
        {
                free(hist_str);
                return (NULL);
        }

        _strcpy(error_msg, name);
        _strcat(error_msg, ": ");
        _strcat(error_msg, hist_str);
        _strcat(error_msg, ": ");
        _strcat(error_msg, args[0]);
        _strcat(error_msg, ": not found \n");

        free(hist_str);
        return (error_msg);
}
