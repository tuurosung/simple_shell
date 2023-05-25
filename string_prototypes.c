#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t i);

/**
 * _strlen - Returns the length of a string.
 * @str: A pointer to the characters string.
 *
 * Return: The length of the character string.
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
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
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
 * _strcat - a function that concatenates two strings
 *
 * @dest: destination
 * @src: source
 *
 * Return: dest
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
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @len: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
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
