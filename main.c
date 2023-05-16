#include "shell.h"

void new_signal(int signal);
int run(char **args, char **front);



int main(int argc, char *argv[])
{
	/* initialize local variables */
	int r = 0;
	int rtn_val;
	int *invk_r = &rtn_val;
	char *cmd = "$ ";
	char *nw_ln = "\n";

	/* set values */
	id = argv[0];
	count = 1;
	aka = NULL;
	signal(SIGINT, sig_handler);

	*invk_r = 0;
	environ = _copyenv(1);

	/* check if environ is valid */
	if (!environ)
		exit(-100);

	/* check argument count */
	if (argc != 1)
	{
		r = proc_file_commands(argv[1], invk_r);
		free_env();
		free_alias_list(aka);
		return(*invk_r);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (r != END_OF_FILE && ret != EXIT)
			r = handle_args(invk_r);
		free_env();
		free_alias_list(aka);
		return (*invk_r);
	}

	while (1)
	{
		write(STDOUT_FILENO, cmd, 2);
		r = handle_args(invk_r);
		if (r == END_OF_FILE || ret == EXIT)
		{
			if (r == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aka);
			exit(*invk_r);
		}
	}

	free_env();
	free_alias_list(aka);
	return (*invk_r);


}
