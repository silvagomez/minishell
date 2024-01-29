
#include "../include/minishell.h"

/*
 * Lexer token tagging
 */
void	tag_token(t_ms *ms, char c, int init, int i)
{
	if (c == '|')
		(lexer_token_last(ms->lexer_token))->tag_pipe = 1;
	if (c == '>' || c== '<')
	{
		(lexer_token_last(ms->lexer_token))->tag_redir += 1;
		if (c == '>')
			(lexer_token_last(ms->lexer_token))->tag_redir += 2;
		if (init != (i - 1))
			(lexer_token_last(ms->lexer_token))->tag_redir += 1;
	}
	if (c == '"')
		(lexer_token_last(ms->lexer_token))->tag_double_q = 1;
	if (c == '\'')
		(lexer_token_last(ms->lexer_token))->tag_single_q = 1;
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

void	join_lexer_tokens(t_ms *ms)
{
	t_lexer_token	*tmp;
	char			*new_arg;

	tmp = ms->lexer_token;
	while (tmp && tmp->next)
	{
		if (!tmp->tag_pipe && !tmp->next->tag_pipe && !tmp->tag_redir && !tmp->next->tag_builtin)
			{
				if (!has_spaces(ms, tmp->end_pos + tmp->tag_double_q + tmp->tag_single_q, tmp->next->init_pos - tmp->tag_double_q - tmp->tag_single_q))
				{
					printf("ENTRO A UNIR ANALIZANDO DESDE %lu HASTA %lu\n", tmp->end_pos + tmp->tag_double_q + tmp->tag_single_q, tmp->next->init_pos - tmp->tag_double_q - tmp->tag_single_q);
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

/*
 * Converts the expanded rline into lexer tokens. 
 * ¡¡Needs refactoring or modularizing!!
 */
void tokenize_rline(t_ms *ms)
{
	int			i;
	int			init;
	char		c;
	t_lexer_token *tmp;
	
	i = 0;
	printf("EXPANDED RLINE: %s\n", ms->rline);
	ms->lexer_token = NULL;
	while (ms->rline[i])
	{
		while (ms->rline[i] == ' ' || ms->rline[i] == '\t')
			i++;
		init = i;
		if (ms->rline[i] == '|' || ms->rline[i] == '>' || ms->rline[i] == '<')
		{
			c = ms->rline[i];
			while (ms->rline[i] && ms->rline[i] == c)
			{
					i++;
				if (c == '|')
					break;
			}
			lexer_token_add(&ms->lexer_token, lexer_token_new(ms, init, i - 1));
			if (ms->lexer_token)
				tag_token(ms, c, init, i);
		}
		else if (ms->rline[i] == '"' || ms->rline[i] == '\'')
			{
				c = ms->rline[i];
				i++;
				while ((ms->rline[i] && ms->rline[i] != c) ||  (ms->rline[i] && ms->rline[i] == c && ms->rline[i - 1] == '\\'))
					i++;
				printf("I VALE: %i\n", i);
				lexer_token_add(&ms->lexer_token, lexer_token_new(ms, init + 1, i - 1));
				if (ms->lexer_token)
					tag_token(ms, c, init, i);
				i++;
			}
		else
		{
			while (ms->rline[i] && ms->rline[i] != ' ' && ms->rline[i] != '\'' && ms->rline[i] != '\t' && ms->rline[i] != '"' && ms->rline[i] != '|' && ms->rline[i] != '<' && ms->rline[i] != '>')
				i++;
			lexer_token_add(&ms->lexer_token, lexer_token_new(ms, init, i - 1));
		}
	}
	//LEXER TOKENS DEFINIDOS
	join_lexer_tokens(ms);
	printf("\nLEXER TOKENS: %i\n", lexer_token_count(ms->lexer_token));
	tmp= ms->lexer_token;
	while (tmp)
		{
			if (tmp->init_pos <= tmp->end_pos)
			{
				printf("\n#%zu: "HYEL"%s - From %i to %i"RST"", tmp->token_id, tmp->arg, tmp->init_pos, tmp->end_pos);
				print_flags_if_present(tmp);
			}
			tmp = tmp->next;
		}
}


