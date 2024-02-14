
#include "minishell.h"

size_t	seek_equal(char *arg)
{
	if (ft_strchr(arg, '='))
		return (1);
	return (0);
}

void	remove_ltoken(t_parser_token *ptoken, size_t idx)
{
	t_lexer_token	*ltoken;

	while (ptoken->lxr_list->token_id != idx)
	{
		ltoken = ptoken->lxr_list;
		ptoken->lxr_list = ptoken->lxr_list->next;
		ptoken->lxr_list->prev = NULL;
		free(ltoken);
	}
}
