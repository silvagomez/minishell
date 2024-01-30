
#include "../include/minishell.h"

int		has_spaces(t_ms *ms, int init, int end)
{
	int	i;

	i = 0;
	while (init + i <= end)
	{
		if(ms->rline[init + i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	delete_lexer_arg(t_ms *ms, int id)
{
	t_lexer_token *tmp;

	tmp = ms->lexer_token;
	while (tmp)
	{
		if ((int)tmp->token_id == id)
			break ;
		tmp = tmp->next;
	}
	if(!tmp->next)
		tmp->prev->next = NULL;
	else if (tmp->next && tmp->prev)
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	}
	free (tmp->arg);
	free (tmp);
}

void	join_lexer_tokens(t_ms *ms)
{
	t_lexer_token	*tmp;
	char			*new_arg;

	tmp = ms->lexer_token;
	while (tmp && tmp->next)
	{
		if (!tmp->tag_pipe && !tmp->next->tag_pipe && !tmp->tag_redir \
				&& !tmp->next->tag_builtin)
		{
			if (!has_spaces(ms, tmp->end_pos + tmp->tag_double_q + \
						tmp->tag_single_q, tmp->next->init_pos - \
						tmp->tag_double_q - tmp->tag_single_q))
			{
				//printf("ENTRO A UNIR ANALIZANDO DESDE %lu HASTA %lu\n", tmp->end_pos + tmp->tag_double_q + tmp->tag_single_q, tmp->next->init_pos - tmp->tag_double_q - tmp->tag_single_q);
				new_arg = ft_strjoin(tmp->arg, tmp->next->arg);
				free(tmp->arg);
				tmp->arg = new_arg;
				delete_lexer_arg(ms, tmp->next->token_id);
			}
				else
					tmp = tmp->next;
			}
		else
			tmp = tmp->next;
	}
}
