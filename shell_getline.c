#include "shell.h"

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t buffer_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - function that resizes memory
 * @ptr: pointer to memory
 * @prev_size: previous memory size
 * @new_size: current memmory size
 * Return: returns new memory size
 */

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
    /* initialize variables */
	void *memory;
	char *ptr_copy, *filler;
	unsigned int i;

    /* check for NULL */
	if (new_size == prev_size)
	return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(new_size);
	if (memory == NULL)
	return (NULL);
	return (memory);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memory = malloc(sizeof(*ptr_copy) * new_size);

	if (memory == NULL)
	{
		free(ptr);
	}

	filler = memory;

	for (i = 0; i < prev_size && i < new_size; i++)
		filler[i] = *ptr_copy++;

	free(ptr);
	return (memory);
}
/**
 * assign_lineptr - that reads user input
 * @lineptr: pointer to user inputs
 * @n: number of inputs
 * @buffer: strings of inputs
 * @buffer_size: size of buffer
 * Return: returns nothing
 */

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t buffer_size)
{
	if (*lineptr == NULL)
	{
	if (buffer_size > 120)
		*n = buffer_size;

	else
	*n = 120;
	*lineptr = buffer;

	}
	else
	{
	_strcpy(*lineptr, buffer);
	free(buffer);
	}
}

/**
 * _getline - function that reads entire line from stream
 *
 * @lineptr: pointer to user input
 * @n: number of inputs
 * @stream: stream to be read
 *
 *Return: returns result
 */


ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t result;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDERR_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}

		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

			buffer[input] = c;
			input++;
	}
	buffer[input] = '\0';
	assign_lineptr(lineptr, n, buffer, input);
	return = input;
	if (r != 0)
	input = 0;
	return (result);
}
