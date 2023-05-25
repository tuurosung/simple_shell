#include "shell.h"

void free_args(char **args, char **front);
char *get_process_id(void);
char *get_envrnment_val(char *start, int len);
void replace_var(char **args, int *ret_val);

/**
 * free_args - a function that frees up the memory used by arguments
 * 
 * @args: double pointer containing arguments
 * @front: address to the beginning of the arguments
*/
void free_args(char **args, char **front)
{
        size_t i;

        for (i = 0; args[i] || args[i + 1]; i++)
                free(args[i]);
        free(front);
}

/**
 * get_process_id - a function that gets the id of the current process
 * 
 * Return: ID or NULL if failed
*/
char *get_process_id(void)
{
        size_t i;
        char *buffer;
        ssize_t file;

        file = open("/proc/self/stat", O_RDONLY);
        if (file == -1)
        {
                perror("Can't read the file");
                return (NULL);
        }

        buffer = malloc(120);
        if (!buffer)
        {
                close(file);
                return (NULL);
        }

        read(file, buffer, 120);

        while(buffer[i] != ' ')
                i++;
        
        buffer[i] = '\0';

        close(file);
        return (buffer);
}

/**
 * get_envrnment_value - a function that get the value of the env variable
 * 
 * @start: the beginning of the env var
 * @len: length of the env var
 * 
 * Return: val of env var.
*/

char *get_envrnment_value(char *start, int len)
{
        char **ptr_var;
        char *swap_var = NULL, *holder, *var;

        var = malloc(len + 1);
        if (!var)
                return (NULL);
        
        var[0] = '\0';
        _strncat(var, start,len);

        ptr_var = _getenv(var);
        free(var);
        if (ptr_var)
        {
                holder = *ptr_var;
                while (*holder != '=')
                        holder++;
                
                holder++;
                swap_var = malloc(_strlen(holder) + 1);
                if (swap_var)
                        _strcpy(swap_var, holder);
        }

        return (swap_var);
}


void variable_replacement(char **line, int *exe_ret)
{
        int j, k = 0, len;
        char *swap_var = NULL, *prev = NULL, *curr;

        prev = *line;

        for (j = 0; prev[j]; j++) 
        {
                if (prev[j] =='&' && prev[j + 1] &&
                        prev[j + 1] != ' ')
                {
                        if (prev[j + 1] == '&')
                        {
                                swap_var = get_process_id();
                                k = j + 2;
                        }
                        else if (prev[j +1] == '?')
                        {
                                swap_var = _itoa(*exe_ret);
                                k = j + 2;
                        }
                        else if (prev[j + 1])
                        {
                                for (k = j + 1; prev[k] && prev[k] != '&' && prev[k] != ' '; k++)
                                        ;

                                len = k - (j +1);
                                swap_var = get_envrnment_val(&prev[j + 1], len);
                        }
                        curr = malloc(j + _strlen(swap_var) + _strlen(&prev[k]) + 1);

                        if (!line)
                                return;
                        curr[0] = '\0';
                        _strncat(curr, prev, j);
                        if (swap_var)
                        {
                                _strcat(curr, swap_var);
                                free(swap_var);
                                swap_var = NULL;
                        }

                        _strcat(curr, &prev[k]);
                        free(prev);
                        *line = curr;
                        prev = curr;
                        j = -1;
                }
        }
}