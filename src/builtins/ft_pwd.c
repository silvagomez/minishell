
#include "minishell.h"

/*
 *  ms->pwd should update every time after cd or go to the next comment ;)
 *  ELSE -> is the bash original way
 */
 int	ft_pwd(t_ms *ms, t_lexer_token *ltoken)
{
	char	pwd[1024];

	if (ltoken->next)
		return (error_handling(ERR_IBOP, EXIT_FAILURE), 1);
	if (ms->pwd)
	{
		ft_printf("%s\n", ms->pwd);
		return (0);
	}
	else
	{
		if (getcwd(pwd, sizeof(pwd)))
		{
			printf("%s\n", pwd);
			return (0);
		}
		else
			error_handling(ERR_DFLT, EXIT_FAILURE);
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
