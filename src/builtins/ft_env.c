#include "minishell.h"

/*
 * This functions will update the *content node of *envlist
 * if node->name is equal of *env_name.
 */
void	update_env_content(t_ms *ms, char *env_name, char *s)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, env_name, ft_strlen(env_name) + 1) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(s);
		}
		tmp = tmp->next;
	}
}

/*
 * This function returns a node from *envlist found by name.
 */
t_envlst	*find_env(t_ms *ms, char *env_name)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, env_name, ft_strlen(env_name) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 * This function returns the content node form *envllist found by name.
 */
char	*ft_getenv(t_ms *ms, char *var_name)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 * This function prints *envlist
 */
void	ft_env(t_ms *ms)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}
