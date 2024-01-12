
#include "minishell.h"

/*
int	ft_echo(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				place;

	tmp = ltoken;
	if (!tmp)
		return (1);
	place = 1;
	if (ptoken->next)
		place = ms->tube[ptoken->token_id];
	if (!ft_strncmp(tmp->arg, "-n", 3))
		ltoken = ltoken->next;
	while (ltoken)
	{
		ft_putstr_fd(ltoken->arg, place);
		if (ltoken->next)
			ft_putchar_fd(' ', place);
		ltoken = ltoken->next;
	}
	if (ft_strncmp(tmp->arg, "-n", 3))
		ft_putchar_fd('\n', place);
	if (ptoken->next)
		close (ms->tube[ptoken->token_id]);
	return (0);
}
*/

int	ft_echo(t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	tmp = ltoken;
	if (!tmp)
		return (1);
	if (!ft_strncmp(tmp->arg, "-n", 3))
		ltoken = ltoken->next;
	while (ltoken)
	{
		ft_printf("%s", ltoken->arg);
		if (ltoken->next)
			ft_printf(" ");
		ltoken = ltoken->next;
	}
	if (ft_strncmp(tmp->arg, "-n", 3))
		ft_printf("\n");
	return (0);
}

