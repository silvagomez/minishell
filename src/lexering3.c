
#include "../include/minishell.h"

t_strlst	*strlst_last(t_strlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	strlst_add(t_strlst **lst, t_strlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		strlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

t_strlst	*strlst_new(t_ms *ms, int init_pos, int end_pos)
{
	t_strlst	*node;

	node = (t_strlst *)ft_calloc(1, sizeof(t_strlst));
	if (!node)
		return (NULL);
	node->str = ft_substr(ms->rline, init_pos, end_pos - init_pos + 1);
	node->idx = init_pos;
	node->next = NULL;
	return (node);
}

void	free_str_lst(t_strlst **list)
{
	t_strlst	*next;

	next = *list;
	while (*list)
	{
		next = (*list)->next;
		free ((*list)->str);
		(*list)->str = NULL;
		free (*list);
		*list = NULL;
		*list = next;
	}
}
