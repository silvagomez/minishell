
#include "minishell.h"

void	free_unset_node(t_envlst *node)
{
	if (node->has_equal)
		free(node->content);
	free(node->name);
	free(node);
	node = NULL;
}

void	pointer_relocation(t_envlst **node, t_envlst **tmp)
{
	if ((*node)->prev && (*node)->next)
	{
		(*node)->next->prev = (*node)->prev;
		(*node)->prev->next = (*node)->next;
	}
	else if ((*node)->prev && !(*node)->next)
		(*node)->prev->next = NULL;
	else if (!(*node)->prev && (*node)->next)
	{
		(*node)->next->prev = NULL;
		(*tmp) = (*tmp)->next;
	}
}

int	ft_unset(t_ms *ms, char *var_name)
{
	t_envlst	*tmp;
	t_envlst	*node;

	if (!var_name)
		return (0);
	if (*var_name == '-')
		return (error_handling(ERR_IBOP, EXIT_FAILURE), 2);
	tmp = ms->envlst;
	node = NULL;
	node = find_env(ms, var_name);
	if (node)
	{
		pointer_relocation(&node, &tmp);
		free_unset_node(node);
		ms->envlst = tmp;
	}
	envlist_to_array(ms, UNSET);
	return (0);
}
