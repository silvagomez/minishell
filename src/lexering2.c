
#include "../include/minishell.h"

char	*expand_var_str(t_ms *ms, t_strlst *tmp)
{
	char	*var_str;

	if (ft_getenv(ms, tmp->str + 1))
		var_str = ft_strdup(ft_getenv(ms, tmp->str + 1));
	else
		var_str = ft_strdup("");
	free (tmp->str);
	return (var_str);
}

void	expand_cases(t_ms *ms, t_strlst *tmp, t_strlst *last)
{
	if (tmp->str[0] == '$' && tmp->str[1] == '$' && !tmp->str[2] \
			&& ms->shadow[tmp->idx] != '1')
	{
		free(tmp->str);
		tmp->str = ft_strdup(ms->pid);
	}
	else if (tmp->str[0] == '$' && tmp->str[1] == '0' && !tmp->str[2] \
			&& ms->shadow[tmp->idx] != '1')
	{
		free(tmp->str);
		tmp->str = ft_strdup("minishell");
	}
	else if (tmp->str[0] == '$' && tmp->str[1] == '?' && !tmp->str[2] \
			&& ms->shadow[tmp->idx] != '1')
	{
		free(tmp->str);
		tmp->str = ft_itoa(g_status);
		//printf("pointer %p\n", tmp->str);
	}
	else if (tmp->str[0] == '$' && tmp->idx > 0 \
			&& ms->rline[tmp->idx - 1] == '\\' && ms->shadow[tmp->idx] != '1')
		last->str[ft_strlen(last->str) - 1] = 0;
	else if (tmp->str[0] == '$' && ms->shadow[tmp->idx] != '1' \
			&& ms->rline[tmp->idx + 1] != ' ' && ms->rline[tmp->idx + 1] \
			&& ms->rline[tmp->idx + 1] != '"')
		tmp->str = expand_var_str(ms, tmp);
}

/*
 * Scans the str_lst list for expandable elements and expands them
 */
void	expand_lst(t_ms *ms)
{
	t_strlst	*tmp;
	t_strlst	*last;

	tmp = ms->str_lst;
	while (tmp)
	{
		expand_cases(ms, tmp, last);
		/*
		if (tmp->str[0] == '$' && tmp->str[1] == '$' && !tmp->str[2] && ms->shadow[tmp->idx] != '1')
			tmp->str = ft_strdup(ms->pid);
		else if (tmp->str[0] == '$' && tmp->str[1] == '0' && !tmp->str[2] && ms->shadow[tmp->idx] != '1')
			tmp->str = ft_strdup("minishell");
		else if (tmp->str[0] == '$' && tmp->str[1] == '?' && !tmp->str[2] && ms->shadow[tmp->idx] != '1')
			tmp->str = ft_strdup(ft_itoa(g_status));
		else if (tmp->str[0] == '$' && tmp->idx > 0 && ms->rline[tmp->idx - 1] == '\\' && ms->shadow[tmp->idx] != '1')
			last->str[ft_strlen(last->str) - 1] = 0; 
		else if (tmp->str[0] == '$' && ms->shadow[tmp->idx] != '1' && ms->rline[tmp->idx + 1] != ' ' && ms->rline[tmp->idx + 1] && ms->rline[tmp->idx + 1] != '"')
			tmp->str = expand_var_str(ms, tmp);
			//tmp->str = var_str;
		*/
		last = tmp;
		tmp = tmp->next;
	}
}
