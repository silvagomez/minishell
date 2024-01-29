
#include "minishell.h"

size_t	size_for_array_envp(t_ms *ms)
{
	size_t		size;
	t_envlst	*tmp;

	size = 0;
	tmp = ms->envlst;
	while (tmp)
	{
		if (tmp->has_equal && tmp->scope)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

void	create_pathlist(t_ms *ms)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (ms->pathlist[i])
	{
		tmp = ms->pathlist[i];
		ms->pathlist[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
}

void	env_to_path(t_ms *ms, t_envlst *envlst)
{
	char	*str;

	while (envlst)
	{
		if (ft_strncmp("PATH", envlst->name, 5) == 0)
		{
			str = ft_strdup(envlst->content);
			break ;
		}
		else
			envlst = envlst->next;
	}
	if (!envlst)
		return;
	ms->pathlist = ft_split(str, ':');
	create_pathlist(ms);
	free(str);
}

void	alloc_envp(t_ms *ms, size_t command)
{
	int			size;

	size = size_for_array_envp(ms);
	if (command == EXPORT)
		ms->envp = (char**) malloc((size + 2) * sizeof(char *));
	else if (command == UNSET)
		ms->envp = (char**) malloc((size + 1) * sizeof(char *));
}

void	envlist_to_array(t_ms *ms, size_t command)
{
	t_envlst	*tmp;
	int			idx;
	char		*str;

	alloc_envp(ms, command);
	tmp = ms->envlst;
	idx = 0;
	str = NULL;
	while (tmp)
	{
		if (tmp->has_equal && tmp->scope)
		{
			str = ft_strjoin(tmp->name, "=");
			ms->envp[idx] = ft_strjoin(str, tmp->content);
			free(str);
			str = NULL;
			idx++;
		}
		tmp = tmp->next;
	}
	ms->envp[idx] = NULL;
	free_string_array(ms->pathlist);
	env_to_path(ms, ms->envlst);
}

