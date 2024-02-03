
#include "minishell.h"

void	free_unset_node(t_envlst *node)
{
	if (node->has_equal)
		free(node->content);
	free(node->name);
	free(node);
	node = NULL;
	//return (free(node->content), free(node->name), free(node));
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
//void	ft_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_envlst	*tmp;
	t_envlst	*node;

	if (!var_name)
		return (0);
	tmp = ms->envlst;
	node = NULL;
	node = find_env(ms, var_name);
	if (node)
	{
		pointer_relocation(&node, &tmp);
		free_unset_node(node);
		ms->envlst = tmp;
	}
	if (!ft_strncmp(var_name, "PATH", ft_strlen(var_name) + 1))
		error_handling(ERR_PATH, 127);
	envlist_to_array(ms, UNSET);
	return (0);
}
