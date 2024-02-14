
#include "minishell.h"

size_t	define_tag(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken)
{
	if (is_builtin(ltoken))
		return (1);
	if (is_command(ms, ltoken))
		return (0);
	return (is_local_var(ptoken));
}

t_parser_token	*parser_token_last(t_parser_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	parser_token_add(t_parser_token **lst, t_parser_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		parser_token_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

int	ptoken_count(t_parser_token *lst)
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

/*
 * node->tag = 0 program or cmd
 * node->tag = 1 built-in
 * node->tag = 2 local var
 */
t_parser_token	*parser_token_new(t_ms *ms, t_lexer_token *lexer_token)
{
	t_parser_token	*node;

	node = (t_parser_token *)ft_calloc(1, sizeof(t_parser_token));
	if (!node)
		return (NULL);
	node->lxr_list = lexer_token;
	node->lxr_list->prev = NULL;
	node->prev = parser_token_last(ms->parser_token);
	node->token_id = ptoken_count(ms->parser_token) + 1;
	node->output_fd = 1;
	node->input_fd = 0;
	node->next = NULL;
	node->tag = define_tag(ms, node, node->lxr_list);
	return (node);
}
