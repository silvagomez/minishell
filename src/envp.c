
#include "minishell.h"

size_t	exist_envp(char **envp)
{
	if (!envp || !*envp)
		return (0);
	return (1);
}

void	fill_envp(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->envp = (char **) malloc (sizeof(char *) * i + 1);
	i = 0;
	while (envp[i])
	{
		ms->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	ms->envp[i] = 0;
	//clean possible env for guarromantics as $_ and $OLDPWD
}

void	set_paths(t_ms *ms)
{
	ms->user = ft_strdup(getenv("USER"));
	ms->ser = ft_strdup(getenv("HOME"));
}

