
#include "minishell.h"

int	err_arg(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (1);
	return (0);
}

/*
 * This functions returns the last node of the list.
 */
t_envlst	*dup_envlst_last(t_envlst *dup_lst)
{
	if (!dup_lst)
		return (NULL);
	while (dup_lst->next != NULL)
		dup_lst = dup_lst->next;
	return (dup_lst);
}

/*
 * This functions adds a node into the dup list of envlst.
 */
void	dup_envlst_add(t_envlst **dup_lst, t_envlst *new_node)
{
	if (!new_node)
		return ;
	if (*dup_lst != NULL)
	{
		new_node->prev = dup_envlst_last(*dup_lst);
		new_node->next = NULL;
		dup_envlst_last(*dup_lst)->next = new_node;
	}
	else
	{
		*dup_lst = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
}

/*
 * This functions creates a new node (dup) of envlst
 */
t_envlst	*dup_envlst_new(t_envlst **dup_lst, t_envlst *envlst_node)
{
	t_envlst	*node;

	node = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->name = ft_strdup(envlst_node->name);
	if (envlst_node->has_equal)
		node->content = ft_strdup(envlst_node->content);
	else
		node->content = NULL;
	node->has_equal = envlst_node->has_equal;
	node->scope = envlst_node->scope;
	node->prev = dup_envlst_last(*dup_lst);
	node->next = NULL;
	return (node);
}

/*
 * This functions returns a *duplist of envlst.
 */
t_envlst	*dup_envlst(t_envlst *envlst)
{
	t_envlst	*dup_lst;
	t_envlst	*envlst_node;

	if (!envlst)
		return (NULL);
	dup_lst = NULL;
	envlst_node = envlst;
	while (envlst_node)
	{
		dup_envlst_add(&dup_lst, dup_envlst_new(&dup_lst, envlst_node));
		envlst_node = envlst_node->next;
	}
	return (dup_lst);
}
