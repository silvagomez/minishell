
#include "minishell.h"

void	append_output(char *content, char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_RDWR | O_CREAT, 0777);
	ft_putstr_fd(content, fd);
	close(fd);
}

void	redirect_output(char *content, char *filename)
{
	int	fd;

	fd = open(filename, O_TRUNC | O_RDWR | O_CREAT, 0777);
	ft_putstr_fd(content, fd);
	close(fd);
}

void	redirect_input(char *content)
{
	ft_putstr_fd(content, 0);
}
