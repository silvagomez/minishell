
#include "minishell.h"

void	export_to_declare(t_ms *ms, t_lexer_token *tmp, int *status)
{
	while (tmp)
	{
		(*status) = ft_export(ms, tmp->arg, 2);
		tmp = tmp->next;
	}
}

/*
 * Scope:
 * 0 = env;
 * 1 = export;
 * 2 = declare;
 */
int	execute_export(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				status;

	tmp = ltoken;
	if (!ft_strncmp(tmp->arg, "export", ft_strlen(tmp->arg) + 1))
	{
		if (tmp->next)
		{
			tmp = tmp->next;
			while (tmp)
			{
				status = ft_export(ms, tmp->arg, 0);
				tmp = tmp->next;
			}
		}
		else
			status = ft_export(ms, NULL, -1);
	}
	else
		export_to_declare(ms, tmp, &status);
	return (status);
}

int	execute_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				status;

	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			status = ft_unset(ms, tmp->arg);
			tmp = tmp->next;
		}
	}
	else
		status = ft_unset(ms, NULL);
	return (status);
}
