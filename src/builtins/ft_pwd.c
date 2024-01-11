
#include "minishell.h"

int	ft_pwd(t_ms *ms)
{
	char	pwd[1024];

	// ms->pwd should update every time after cd or go to the next comment ;)
	if (ms->pwd)
	{
		ft_printf("%s\n", ms->pwd);
		return (0);
	}
	// this is the bash original way
	else
	{
		if (getcwd(pwd, sizeof(pwd)))
		{
			printf("%s\n", pwd);
			return (0);
		}
		else
			ft_putendl_fd("ERRRRRRRROOOOOORRRR", 2);
	}
	return (1);
}

char	*get_pwd(void)
{
	char	pwd[1024];
	char	*gpwd;

	if (getcwd(pwd, sizeof(pwd)))
	{
		gpwd = pwd;
		return (gpwd);
	}
	else
		return (NULL);
}
