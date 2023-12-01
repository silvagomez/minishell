
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
 * This function returns the last node of the env linked list.
 */
t_envlst	*envlst_last(t_envlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*
 * This function adds a node into envlist.
 */
void	envlst_add(t_envlst **lst, t_envlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		envlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

/*
 * This function creates a *node of envlist.
 */
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

/*
 * This function creates ms->envlst.
 */
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
