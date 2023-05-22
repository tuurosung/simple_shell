#include "shell.h"

/**
 * main - main entry level
 *
 * Return: returns 0 success
 */
#define BUFSIZE 1024

int main (int argc, char *argv[],char *envp[])
{
	char *command =  malloc(BUFSIZE);
	char *args[BUFSIZE];
	char *token;
	int nread;
	char prompt[] = "$";

	while (1)
	{
		write(STDOUT_FILENO, prompt, 1);
		nread = read(STDIN_FILENO, command, BUFSIZE); /*taking input from user*/

		if (nread == -1)
		{
			if(feof(stdin))
			{
			break;
			}
			perror("read");
			errno = EINTR;


		}

		else
		{
			token = strtok(command, "\n");
			int i = 0;
			while (!token)
			{
			
				args[1]  = token;
				i++;
				token = strtok(NULL, "\n");

			}

			args[i] = NULL;

			/*child process*/

			pid_t my_child;
			int status;
			my_child = fork();

			if (my_child == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);

			}
			else if (my_child == 0)
			{
				execve(args[i], args, envp);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(my_child, &status, 0);
			}

		}

	}

	free(command);
	return (0);
}
