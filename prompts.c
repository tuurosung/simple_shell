#include "shell.h"


int validate_prompt(info_t *info, char *dir)
{
	struct stat st;

	(void)info;
	if (!dir || stat(dir, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}



char *dup_chars(char *dir_path, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (dir_path[i] != ':')
			buf[k++] = dir_path[i];
	buf[k] = 0;
	return (buf);
}


char *find_path(info_t *info, char *dir_path, char *prompt)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!dir_path)
		return (NULL);
	if ((_strlen(prompt) > 2) && compare_head(prompt, "./"))
	{
		if (validate_prompt(info, prompt))
			return (prompt);
	}
	while (1)
	{
		if (!dir_path[i] || dir_path[i] == ':')
		{
			path = dup_chars(dir_path, curr_pos, i);
			if (!*path)
				_strcat(path, prompt);
			else
			{
				_strcat(path, "/");
				_strcat(path, prompt);
			}
			if (validate_prompt(info, path))
				return (path);
			if (!dir_path[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
