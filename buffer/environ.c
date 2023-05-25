#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - a function that returns a copy of the environment
 *
 * Return: an address of the environment variable
*/
char **_copyenv(void)
{
	/* initialize variables */
	char **new_envrnment = NULL;
	size_t env_size;
	int i;

	/* loop through till actual size is reached*/
	for (env_size = 0; environ[env_size]; env_size++)
		;

	new_envrnment = malloc(sizeof(char *)  * (env_size + 1));

	/* check for NULL */
	if (!new_envrnment)
		return (NULL);


	for (i = 0; environ[i]; i++)
	{
		new_envrnment[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_envrnment[i])
		{
			for (i--; i >= 0; i--)
				free(new_envrnment[i]);

			free(new_envrnment);
			return (NULL);
		}

		_strcpy(new_envrnment[i], environ[i]);
	}

	new_envrnment[i] = NULL;
	return (new_envrnment);
}

/**
 * free_env - a function that frees the newly copied environment
*/

void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}


/**
 * _getenv - a function that gets the env var from the Global PATH
 *
 * @env_var: the name of the env var
 * Return: NULL is not exists or address to env var.
*/

char **_getenv(const char *env_var)
{
	/* initialize variables */
	int i;
	int var_len = _strlen(env_var);

	/* loop through till var address if retrieved */
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(env_var, environ[i], var_len) == 0)
			return (&environ[i]);
	}

	return (NULL);
}