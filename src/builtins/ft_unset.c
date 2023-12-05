
#include "minishell.h"

void	ft_unset(t_ms *ms, char *var_name)
{
	t_envlst *tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
			{
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				return(free (tmp->content), free (tmp->name), free(tmp));
			}
		tmp = tmp->next;
	}
}
