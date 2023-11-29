
#include "minishell.h"

size_t	exist_envp(char **envp)
{
	if (!envp || !*envp)
		return (0);
	return (1);
}

t_envlst	*envlst_last(t_envlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	envlst_add(t_envlst **lst, t_envlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		envlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

t_envlst	*envlst_new(t_ms *ms, char *line)
{
	t_envlst	*node;

	node = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->name = ft_substr(line, 0, (ft_strchr(line, '=') - line));
	node->content = ft_strdup(ft_strchr(line, '=') + 1);
	node->prev = envlst_last(ms->envlst);
	node->next = NULL;
	return (node);
}

void	fill_envp(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		envlst_add(&ms->envlst, envlst_new(ms, envp[i]));
		i++;
	}
}


/*
 * This will be deleted after ft_export is okay
 */
void	ft_export(t_ms *ms, char *arg)
{
	t_envlst	*tmp;
	char		*var_name;
	char		*content;

	var_name = ft_substr(arg, 0, (ft_strchr(arg, '=') - arg));
	content = ft_strdup(ft_strchr(arg, '=') + 1);
	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
		{
			free (tmp->content);
			tmp->content = content;
			free (var_name);
			return;
		}
		tmp = tmp->next;
	}

	envlst_add(&ms->envlst, envlst_new(ms, arg));
	free (var_name);
	free (content);
}
