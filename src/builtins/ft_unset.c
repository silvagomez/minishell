
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

void	ft_unset(t_ms *ms, char *var_name)
//void	ft_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_envlst	*tmp;
	t_envlst	*node;

	//if (!ltoken->arg)
	if (!var_name)
		return ;
	tmp = ms->envlst;
	node = NULL;
	//node = find_env(ms, ltoken->arg);
	node = find_env(ms, var_name);
	if (node)
	{
		//ft_printf(RED"moviendo nodos\n"RST);
		if (node->prev && node->next)
		{
			//printf(HMAG"1prev %p ### %p %s %s ## next %p\n"RST, node->prev, node, node->name, node->content, node->next);
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}
		else if (node->prev && !node->next)
		{
			//printf(MAG"2prev %p ### %p %s %s ## next %p\n"RST, node->prev, node, node->name, node->content, node->next);
			node->prev->next = NULL;

		}
		else if (!node->prev && node->next)
		{
			//printf(HCYN"3prev %p ### %p %s %s ## next %p\n"RST, node->prev, node, node->name, node->content, node->next);
			node->next->prev = NULL;
			tmp = tmp->next;
		}
		free_unset_node(node);
		ms->envlst = tmp;
	}
	//ft_printf(RED"Size de envlst %i\n"RST, envlst_node_count(ms->envlst));
	//ft_printf(RED"Size de tmp %i\n"RST, envlst_node_count(tmp));
	envlist_to_array(ms, UNSET);
	//ft_printf(RED"uuuuuuu\n"RST);
	/*
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			return (free(tmp->content), free(tmp->name), free(tmp));
		}
		tmp = tmp->next;
	}
	*/
}
