
#include "minishell.h"

void	error_handling(char *s, int status)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(status);
}
