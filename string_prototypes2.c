#include "shell.h";


char *_strchr(char *s, char c);
int _strspn(char *str, char *match);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t len);


char *_strchr(char *s, char c)
{
    int i;

    for (i = 0; i < s[i]; i++) 
    {
        if (s[i] == c)
            return (s + i);
    }

    return (NULL);
}


int _strspn(char *s, char *match)
{
    int bytes = 0;
    int i;

    /* loop to check for match */
    while (*s)
    {
        for (i = 0; match[i]; i++)
        {
            if (*s == match[i])
            {
                bytes++;
                break;
            }
        }
        return (bytes);
    }
}




int _strcmp(char *str1, char *str2)
{
    while (*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }

    if (*str1 != *str2)
        return (*str1 - *str2);
    
    return (0);
}


int _strncmp(const char *str1, const char *str2, size_t len)
{
    size_t i;

    for (i = 0; str1[i] && str2[i] && i < len; i++)
    {
        if (str1[i] > str2[i])
            return (str1[i] - str2[i]);

        else if (str1[i] < str2[i])
            return (str1[i] - str2[i]);
    }

    if (i == len)
        return (0);
    
    else
        return (-15);
}