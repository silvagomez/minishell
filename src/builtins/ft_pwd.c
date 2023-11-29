
#include "minishell.h"

void	ft_pwd(t_ms *ms)
{
	char	pwd[1024];

	// ms->pwd should update every time after cd or go to the next comment ;)
	if(ms->pwd)
	{
		printf("%s\n", ms->pwd);
	}
	// this is the bash original way
	else
	{
		if (getcwd(pwd, sizeof(pwd)))
			printf("%s\n", pwd);
		else
			ft_putendl_fd("ERRRRRRRROOOOOORRRR", 2);
	}
}
