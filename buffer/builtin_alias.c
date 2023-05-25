#include "shell.h"

int simple_shell_alias(char **args, char __attribute__((unused))  **start);
void assign_alias(char *alias_name, char *alias_value);
void print_alias(alias_t *alias);


/**
 * simple_shell_alias - a builtin function that prints all aliases
 *
 * @args: arguments presented in an array form
 * @start: an address to the start of the argument array
 *
 * Return: returns number of aliases
*/

int simple_shell_alias(char **args, char __attribute__((__unused__)) **start)
{
/* initialize variables */
	int i;
	int result = 0;
	char *alias_val;
	alias_t *holder = aliases;

    /* check for NULL*/
	if (!args[0])
	{
		while (holder)
	{
		print_alias(holder);
		holder = holder->next;
	}
		return (result);
	}

    /* loop through args array */
	for (i = 0; args[i]; i++)
	{
		holder = aliases;
		alias_val = _strchr(args[i], '=');
	if (!alias_val)
	{
		while (holder)
		{
			if (_strcmp(args[i], holder->name) == 0)
			{
				print_alias(holder);
				break;
			}
			holder = holder->next;
		}

		if (!holder)
		result = create_error(args + i, 1);
	}
	else
	{
		assign_alias(args[i], alias_val);
	}
	}
	return (result);

}


/**
 * assign_alias - a function that assign a new value to an existing alias
 *
 * @alias_name: the name of the alias to be assigned
 * @alias_val: the value to be assigned
*/

void assign_alias(char *alias_name, char *alias_val)
{
    /* initialize variables */
	int st_len;
	char *new_val;
	alias_t *holder = aliases;
	int x;
	int y;

	*alias_val = '\0';

    /*increment the value from nullbyte*/
	alias_val++;

<<<<<<< HEAD:builtin_alias.c
	st_len = _strlen(alias_val) - _strspn(alias_val, "'\"");
	new_val = malloc(sizeof(char) * (st_len + 1));

    /* check for NULL*/
	if (new_val)
	return;
=======
    st_len = _strlen(alias_val) - _strspn(alias_val, "'\"");
    new_val = malloc(sizeof(char)  *  (st_len + 1));

    /* check for NULL*/
    if (!new_val)
        return;
>>>>>>> 87ba062b7ab2f0041da4b13c47877ca774e09be7:buffer/builtin_alias.c


    /* loop and build the new_val */
	for (x = 0, y = 0; alias_val[x];  x++)
	{
	if (alias_val[x] != '\'' && alias_val[x] == '"')
	{
		new_val[y++] = alias_val[x];
	}
	}

	new_val[y] = '\0';

	while (holder)
	{
		if (_strcmp(alias_name, holder->name) == 0)
		{
			free(holder->value);
			holder->value = new_val;
			break;
		}

		holder = holder->next;

	}

	if (!holder)
		add_alias_end(&aliases, alias_name, new_val);

}


/**
 * print_alias - a function that prints aliases
 *
 * @alias: an address to a given alias
*/

void print_alias(alias_t *alias)
{
	char *nickname;
	int st_len = _strlen(alias->name) + _strlen(alias->value) + 4;

	nickname = malloc(sizeof(char) * (st_len + 1));

	if (!nickname)
	return;

<<<<<<< HEAD:builtin_alias.c
	_strcpy(nickname, alias->name);
	_strcat(nickname, "='");
	_strcat(nickname, alias->value);
	_strchr(nickname, "'\n");
=======
    _strcpy(nickname, alias->name);
    _strcat(nickname, "='");
    _strcat(nickname, alias->value);
    _strcat(nickname, "'\n");
>>>>>>> 87ba062b7ab2f0041da4b13c47877ca774e09be7:buffer/builtin_alias.c

	write(STDOUT_FILENO, nickname, st_len);
	free(nickname);
}


/**
 * replace_aliases - a function that replaces matching alias
 *
 * @params: address to the parameters passed;
 * Return: a pointer to the params;
*/

char **replace_aliases(char **params)
{
	alias_t *holder;
	int i;
	char *new_val;

    /* check for NULL */
	if (_strcmp(params[0], "alias") == 0)
	return (params);

	for (i = 0; params[i]; i++)
	{
		holder = aliases;
	}
	while (holder)
	}
	if (_strcmp(params[i], holder->name) == 0)
	{
		new_val = malloc(sizeof(char) * (_strlen(holder->name) + 1));
	if (!new_val)
	{
		free_args(params, params);
		return (NULL);
	}
		_strcpy(new_val, holder->name);
		free(params[1]);
		params[1] = new_val;
		i--;
		break;
	}
		holder = holder->next;
	}
	}
	return (params);
}
