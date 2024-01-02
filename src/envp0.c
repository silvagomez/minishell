
#include "minishell.h"
/*
 * This function is used at the beginining to check if our minishell is 
 * receiving the original env.
 */
size_t	exist_envp(char **envp)
{
	if (!envp || !*envp)
		return (0);
	return (1);
}

/*
 * This function returns the size of **envp.
 */
size_t	envp_size(char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

/*
 * This function duplicates the **envp.
 */
void	dup_envp(t_ms *ms, char **envp)
{
	size_t	size;
	size_t	idx;

	size = envp_size(envp);
	ms->envp = (char **)malloc((size + 1) * sizeof(char*));
	idx = -1;
	while (envp[++idx])
		ms->envp[idx] = ft_strdup(envp[idx]);
	ms->envp[idx] = NULL;
}

/*
 * This function dup envp and creates ms->envlst.
 */
void	fill_envp(t_ms *ms, char **envp)
{
	int	i;

	dup_envp(ms, envp);
	i = -1;
	while (envp[++i])
		envlst_add(&ms->envlst, envlst_new(ms, envp[i]));
}
