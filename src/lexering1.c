
#include "../include/minishell.h"

void	rline_var_to_lst(t_ms *ms, int *start, int *end)
{
	(*end)++;
	while (ms->rline[*end] && ms->rline[*end] != ' ' && ms->rline[*end] != '$' \
			&& ms->rline[*end] != '"' && ms->rline[*end] != '\'' \
			&& ms->rline[*end] != '/' && ms->rline[*end] != '?')
		(*end)++;
	strlst_add(&ms->str_lst, strlst_new(ms, *start, *end - 1));
}

/*
 * This function divides the ms->rline into str_lst tokens,
 * according to whether they are expandable or no 
 */
void	rline_to_lst(t_ms *ms, int start, int end)
{
	ms->str_lst = NULL;
	while (ms->rline[start])
	{
		if (ms->rline[start] == '$' && (ms->rline[start + 1] == '$' || \
					ms->rline[start + 1] == '0' || ms->rline[start + 1] == '?'))
		{
			end += 2;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		else if (ms->rline[start] == '$' && ms->rline[start + 1] != ' ')
			rline_var_to_lst(ms, &start, &end);
		else
		{
			if (ms->rline[end] == '$')
				end++;
			while (ms->rline[end] && ms->rline[end] != '$')
				end++;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		start = end;
	}
}

/*
 * Scans the str_lst list for expandable elements and expands them
 */
void	expand_lst(t_ms *ms)
{
	t_strlst	*tmp;
	t_strlst	*last;
	char		*var_str;

	tmp = ms->str_lst;
	while (tmp)
	{
		if (tmp->str[0] == '$' && tmp->str[1] == '$' && !tmp->str[2] && ms->shadow[tmp->index] != '1')
			tmp->str = ft_strdup(ms->pid);
		else if (tmp->str[0] == '$' && tmp->str[1] == '0' && !tmp->str[2] && ms->shadow[tmp->index] != '1')
			tmp->str = ft_strdup("minishell");
		else if (tmp->str[0] == '$' && tmp->str[1] == '?' && !tmp->str[2] && ms->shadow[tmp->index] != '1')
			tmp->str = ft_strdup(ft_itoa(g_status));
		else if (tmp->str[0] == '$' && tmp->index > 0 && ms->rline[tmp->index - 1] == '\\' && ms->shadow[tmp->index] != '1')
			last->str[ft_strlen(last->str) - 1] = 0; 
		else if (tmp->str[0] == '$' && ms->shadow[tmp->index] != '1' && ms->rline[tmp->index + 1] != ' ' && ms->rline[tmp->index + 1] && ms->rline[tmp->index + 1] != '"')
		{
			if (ft_getenv(ms, tmp->str + 1))
				var_str = ft_strdup(ft_getenv(ms, tmp->str + 1));
			else
				var_str = ft_strdup("");
			free (tmp->str);
			tmp->str = var_str;
		}
		last = tmp;
		tmp = tmp->next;
	}
}

/* 
 * I have created *tmp_strlst to copy ms->str_lst cuz the pointer move at 
 * the end of the list = null.
 */
void	expanding(t_ms *ms)
{
	char		*expanded;
	char		*tmp;
	t_strlst	*tmp_strlst;

	rline_to_lst(ms, 0, 0);
	expand_lst(ms);
	expanded = ft_strdup("");
	tmp_strlst = ms->str_lst;
	while (tmp_strlst)
	{
		tmp = expanded;
		expanded = ft_strjoin(expanded, tmp_strlst->str);
		free (tmp);
		tmp_strlst = tmp_strlst->next;
	}
	if (ms->rline)
		free (ms->rline);
	free_str_lst(ms->str_lst);
	ms->rline = expanded;
}
