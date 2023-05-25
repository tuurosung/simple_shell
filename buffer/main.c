#include "shell.h"

void new_signal(int signal);
int run(char **args, char **front);

void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void) sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}



int main(int argc, char *argv[])
{

	/* initialize local variables */
	int ret = 0;
	int retn;
	int *exe_ret = &retn;
	char *prompt = "$ ";
	char *new_line = "\n";

	/* set values */
	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();

	/* check if environ is valid */
	if (!environ)
		exit(-100);

	/* check argument count */
	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);

}
