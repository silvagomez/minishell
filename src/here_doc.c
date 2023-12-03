
#include "minishell.h"

t_hdlst	*hdlst_last(t_hdlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	hdlst_add(t_hdlst **lst, t_hdlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		hdlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

int	hdlst_count(t_hdlst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_hdlst	*hdlst_new(char *str)
{
	t_hdlst	*node;

	node = (t_hdlst *)ft_calloc(1, sizeof(t_hdlst));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

void	hdlst_delete (t_parser_token *ptoken, t_hdlst *node)
{
	ptoken->hd_list = node->next;
	free (node->str);
	free(node);
}