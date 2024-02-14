
#include "minishell.h"

int	pid_token_count(t_pid_token *lst)
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

t_pid_token	*pid_token_new(t_ms *ms, int pid)
{
	t_pid_token	*node;

	node = (t_pid_token *)ft_calloc(1, sizeof(t_pid_token));
	if (!node)
		return (NULL);
	node->id = pid_token_count(ms->pid_token) + 1;
	node->child_pid = pid;
	node->child_status = 0;
	node->next = NULL;
	return (node);
}

t_pid_token	*pid_token_last(t_pid_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	pid_token_add(t_pid_token **lst, t_pid_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		pid_token_last(*lst)->next = new_node;
	else
		*lst = new_node;
}
