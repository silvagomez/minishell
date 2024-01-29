
#include "../include/minishell.h"

t_lexer_token	*lexer_token_last(t_lexer_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lexer_token_add(t_lexer_token **lst, t_lexer_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		lexer_token_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

int	lexer_token_count(t_lexer_token *lst)
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

t_lexer_token	*lexer_token_new(t_ms *ms, int init_pos, int end_pos)
{
	t_lexer_token	*node;

	if (end_pos < init_pos)
		return (NULL);
	printf(HBLK"CREO DE %i a %i\n"RST, init_pos, end_pos);
	node = (t_lexer_token *)ft_calloc(1, sizeof(t_lexer_token));
	if (!node)
		return (NULL);
	node->init_pos = init_pos;
	node->end_pos = end_pos;
	node->arg = ft_substr(ms->rline, init_pos, end_pos - init_pos + 1);
	node->prev = lexer_token_last(ms->lexer_token);
	node->token_id = lexer_token_count(ms->lexer_token) + 1;
	node->next = NULL;
	return (node);
}
