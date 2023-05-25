#include "shell.h"

int token_len(char *str, char *terminus);
int count_tokens(char *str, char *terminus);
char **_strtok(char *line, char *terminus);

int token_len(char *str, char *terminus)
{
        int index = 0, len = 0;

        while (*(str + index) && *(str + index) != *terminus)
        {
                len++;
                index++;
        }

        return (len);
}

int count_tokens(char *str, char *terminus)
{
        int index, tokens = 0, len = 0;

        for (index = 0; *(str + index); index++)
                len++;

        for (index = 0; index < len; index++)
        {
                if (*(str + index) != *terminus)
                {
                        tokens++;
                        index += token_len(str + index, terminus);
                }
        }

        return (tokens);
}

char **_strtok(char *line, char *terminus)
{
        char **ptr;
        int index = 0, tokens, t, letters, l;

        tokens = count_tokens(line, terminus);
        if (tokens == 0)
                return (NULL);

        ptr = malloc(sizeof(char *) * (tokens + 2));
        if (!ptr)
                return (NULL);

        for (t = 0; t < tokens; t++)
        {
                while (line[index] == *terminus)
                        index++;

                letters = token_len(line + index, terminus);

                ptr[t] = malloc(sizeof(char) * (letters + 1));
                if (!ptr[t])
                {
                        for (index -= 1; index >= 0; index--)
                                free(ptr[index]);
                        free(ptr);
                        return (NULL);
                }

                for (l = 0; l < letters; l++)
                {
                        ptr[t][l] = line[index];
                        index++;
                }

                ptr[t][l] = '\0';
        }
        ptr[t] = NULL;
        ptr[t + 1] = NULL;

        return (ptr);
}