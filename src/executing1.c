
#include "minishell.h"

void	execute_export(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			ft_export(ms, tmp->arg);
			tmp = tmp->next;
		}
	}
	else
		ft_export(ms, NULL);
}

void	execute_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			ft_unset(ms, tmp->arg);
			tmp = tmp->next;
		}
	}
	else
		ft_unset(ms, NULL);
}
