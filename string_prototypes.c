#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t i);

/**
 * _strlen - function that prints lenght of a string
 * @str: string to be checked
 * Return: returns length
 */
int _strlen(const char *str)
{
	int len = 0;

	if (!str)
	return (len);

	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - function that copies the string pointed to
 * @dest: pointer to destination string
 * @src: string to be copied
 * Return: returns pointer to destination string
 */


char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - fuction the concatenates one string to another
 * @dest: pointer to destionation string
 * @src: source string
 * Return: returns pointer to destination string
 */

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
/**
 * _strncat - appends characters from one string to the end of another string
 * @dest: pointer to destination string
 * @src: string to be appended
 * @len: number of character
 * Return: returns pointer to destination string
 */

char *_strncat(char *dest, const char *src, size_t len)
{
	size_t i;
	size_t dest_len = _strlen(dest);

	for (i = 0; i < len && src[i] != '\n'; i++)
	dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return (dest);
}
