
#include "minishell.h"

void	ft_echo(t_parser_token *ptoken, t_lexer_token *ltoken)
{
	while (ltoken)
	{
		ft_putendl_fd(ltoken->arg, ptoken->output_fd);
		ltoken = ltoken->next;
	}
}
