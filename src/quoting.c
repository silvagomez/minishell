
#include "minishell.h"

void	check_quote_char(t_ms *ms)
{
	ms->quote = 0;
	if (ft_strchr(ms->rline, '\'') && ft_strchr(ms->rline, '"'))
	{
		if (ft_strchr(ms->rline, '\'') < ft_strchr(ms->rline, '"'))
			ms->quote = '\'';
		else
			ms->quote = '"';
	}
	else if (ft_strchr(ms->rline, '\''))
		ms->quote = '\'';
	else if (ft_strchr(ms->rline, '"'))
		ms->quote = '"';
}

int	is_valid_quoting(t_ms *ms)
{
	check_quote_char(ms);
	if (ms->quote)
	{
		if (ft_strchr(ms->rline, ms->quote) == ft_strrchr(ms->rline, \
			ms->quote))
			return (0);
	}
	return (1);
}
