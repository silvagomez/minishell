
#include "minishell.h"

void	error_handling_exit(char *s, int status)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(status);
}

void	error_handling(char *s, int status)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	g_status = status;
}
