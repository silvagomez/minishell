
#include "minishell.h"

void	ft_echo(t_parser_token *ptoken, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	(void)ptoken;
	tmp = ltoken;
	if (!tmp)
		return ;
	write(1,"ECHO...\n",8);
	system("lsof -c minishell");
	if (!ft_strncmp(tmp->arg, "-n", 3))
		ltoken = ltoken->next;
	while (ltoken)
	{
		ft_putstr_fd(ltoken->arg, TUBE);
		if (ltoken->next)
			ft_putchar_fd(' ', STDIN_FILENO);
		ltoken = ltoken->next;
	}
	if (ft_strncmp(tmp->arg, "-n", 3))
		ft_putchar_fd('\n', STDIN_FILENO);
}
