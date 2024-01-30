
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
