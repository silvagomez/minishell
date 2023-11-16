
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
	ms->envp[i] = NULL;
}

void	default_envp(t_ms *ms, char *env, char *s)
{
	size_t	i;

	i = 0;
	while (ms->envp[i])
	{
		//printf(GREEN"%zu "RESET" %s\n", i , ms->envp[i]);
		if (ft_strncmp(ms->envp[i], env, ft_strlen(env)) == 0)
		{
			//printf(BLUE"found in %zu\n"RESET, i);
			free(ms->envp[i]);
			ms->envp[i] = ft_strjoin(env, s);
			//printf(GREEN"%zu "RESET" %s\n", i , ms->envp[i]);
		}
		i++;
	}
	//i = 0;
	//while (ms->envp[i])
	//{
	//	printf(RED"%zu "RESET" %s\n", i , ms->envp[i]);
	//	i++;
	//}
}

void	set_paths(t_ms *ms)
{
	ms->user = ft_strdup(getenv("USER"));
	ms->home = ft_strdup(getenv("HOME"));
	//clean possible env for guarromantics as $_ and $OLDPWD
	default_envp(ms, "_=", "/usr/bin/env");
	//here we should seek for the test and info if we can null or getenv("PWD") as linux
	default_envp(ms, "OLDPWD=", "");
}

