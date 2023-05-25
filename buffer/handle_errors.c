#include "shell.h"

int number_len(int number);
char *_itoa(int number);
int create_error(char **args, int error_code);

/**
 * number_len - functions tat prints lenght of arguments
 * @number: length of arguments
 * Return: returns lenght of arguments
 */
int number_len(int number)
{
	unsigned int first_num;
	int len = 1;

	if (number < 0)
	{
		len++;
		first_num = number * -1;
	}
	else
	{
	first_num = number;
	}

    /* loop to get length*/
	while (number > 9)
	{
		len++;
		first_num /= 10;
	}

	return (len);
}

/**
 * _itoa - fuction that prints number of  arguments
 * @number: number to be checked
 * Return: returns number of arguments
 */

char *_itoa(int number)
{
	char *buff;
	int len = number_len(number);
	unsigned int first_num;

	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
	return (NULL);

	buff[len] = '\0';

	if (number < 0)
	{
		first_num = number * -1;
		buff[0] = '-';
	}
	else
	{
		first_num = number;
	}

	len--;
	do {
		buff[len] = (first_num % 10) + '0';
		first_num /= 10;
		len--;
	} while (first_num > 0);

	return (buff);

}

/**
 * create_error- function that generates error code
 *
 * @args: strings to be checked
 * @error_code: allocated number to error code
 *
 * Return: returns error code
 */


int create_error(char **args, int error_code)
{
	char *error;

	switch (error_code)
	{
		case -1:
		error = error_env(args);
		break;

		case 1:
		error = error_1(args);
		break;

		case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);

		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);

		else
			error = error_2_cd(args);
			break;
		case 126:
			error = error_126(args);
			break;

		case 127:
			error = error_127(args);
			break;
	}

	write(STDERR_FILENO, error, _strlen(error));

	if (error)
	free(error);
	return (error_code);
}
