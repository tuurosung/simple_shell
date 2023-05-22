#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t i);

int _strlen(const char *str)
{
    int len = 0;

    if (!str)
        return (len);

    for (len = 0; str[len]; len++)
    ;
    return (len);
}



char *_strcpy(char *dest, const char *src)
{
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}


char *_strcat(char *dest, const char *src)
{
    char *temp_dest = dest;
    const char *temp_src = src;

    while (*temp_dest != '\0')
        temp_dest++;

    while (*temp_src != '\0')
        *temp_dest++ = *temp_src++;
    
    *temp_dest = '\0';
    return (dest);
}


char *_strncat(char *dest, const char *src, size_t len)
{
    size_t i;
    size_t dest_len = _strlen(dest);   

    for (i = 0; i < len && src[i] != '\n'; i++)
        dest[dest_len + i] = src[i];

    dest[dest_len + i] = '\0';

    return (dest);
}