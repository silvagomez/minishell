
#include "minishell.h"

void	ft_echo(t_parser_token *ptoken, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	(void)ptoken;
	tmp = ltoken;
	if (!tmp)
		return ;
	if (!ft_strncmp(tmp->arg, "-n", 3))
		ltoken = ltoken->next;
	while (ltoken)
	{
		ft_putstr_fd(ltoken->arg, STDOUT_FILENO);
		if (ltoken->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ltoken = ltoken->next;
	}
	if (ft_strncmp(tmp->arg, "-n", 3))
		ft_putchar_fd('\n', STDOUT_FILENO);
}
