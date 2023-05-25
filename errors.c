#include "shell.h"



void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}



int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}



int fd_put(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}



int _handle_fd_puts(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += fd_put(*str++, fd);
	}
	return (i);
}
