
#include "minishell.h"

void	execute_export(t_ms *ms, t_lexer_token *ltoken)
{
	if (ltoken->next)
		ft_export(ms, ltoken->next->arg);
	else
		ft_export(ms, NULL);
}
