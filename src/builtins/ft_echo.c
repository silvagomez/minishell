
#include "minishell.h"

void	ft_echo(t_parser_token *ptoken, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	tmp = ltoken;
	if (!tmp)
		return ;
	if (!ft_strncmp(tmp->arg, "-n", 3))
		ltoken = ltoken->next;
	while (ltoken)
	{
		ft_putstr_fd(ltoken->arg, ptoken->output_fd);
		if (ltoken->next)
			ft_putchar_fd(' ', ptoken->output_fd);
		ltoken = ltoken->next;
	}
	if (ft_strncmp(tmp->arg, "-n", 3))
		ft_putchar_fd('\n', ptoken->output_fd);
}
