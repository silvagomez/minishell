
#include "../include/minishell.h"

/*Auxiliary function for "create_shadow" to make the code more modular*/
void	fill_shadow(t_ms *ms, int *i, char quote)
{
	if (quote == '\'')
		ms->shadow[(*i)++] = '1';
	else
		ms->shadow[(*i)++] = '2';
}

void	define_spaces_in_shadow(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->rline && ms->rline[++i])
		{
			if (ms->rline[i] == ' ' && ms->shadow[i] != '1' && ms->shadow[i] != '2')
				ms->shadow[i] = '8';
		}
}
/*Function that creates the shadow string. +4 lines that will be removed later*/
int	create_shadow(t_ms *ms)
{
	int		i;
	char	quote;

	i = 0;
	if (ms->rline)
		ms->shadow = calloc(sizeof(char), (ft_strlen(ms->rline) + 1));
	if (ms->rline)
		ft_memset(ms->shadow, '0', ft_strlen(ms->rline));
	while (ms->rline && ms->rline[i])
	{
		if (ms->rline[i] == '"' || ms->rline[i] == '\'')
		{
			quote = ms->rline[i];
			fill_shadow(ms, &i, quote);
			while ((ms->rline[i] && ms->rline[i] != quote) || (ms->rline[i] && ms->rline[i] == quote && ms->rline[i - 1] == '\\'))
				fill_shadow(ms, &i, quote);
			if (!ms->rline[i])
			{
				ms->shadow[i] = 'E';
				return (ft_printf(HRED"ERROR COMILLAS SIN CERRAR\n"RST), 0);
			}
			fill_shadow(ms, &i, quote);
		}
		else
			i++;
	}
	define_spaces_in_shadow(ms);
	printf("\nSHADOW: %s\n", ms->shadow);
	return (1);
}

void	print_flags_if_present(t_lexer_token *token)
{
	if (token->tag_program)
		printf(GRN"\t(PROGRAM: %zu)"RST, token->tag_program);
	if (token->tag_builtin)
		printf(GRN"\t(BUILTIN: %zu)"RST, token->tag_builtin);
	if (token->tag_double_q)
		printf(GRN"\t(DOUBLE_Q: %zu)"RST, token->tag_double_q);
	if (token->tag_single_q)
		printf(GRN"\t(SINGLE_Q: %zu)"RST, token->tag_single_q);
	if (token->tag_redir)
		printf(GRN"\t(REDIR: %zu)"RST, token->tag_redir);
	if (token->tag_pipe)
		printf(GRN"\t(PIPE: %zu)"RST, token->tag_pipe);
	if (token->tag_spec_char)
		printf(GRN"\t(SPEC_CHAR: %zu)"RST, token->tag_spec_char);
}
/*Lexer token tagging*/
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
/*Converts the expanded rline into lexer tokens. ¡¡Needs refactoring or modularizing!!*/
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

t_strlst	*strlst_last(t_strlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	strlst_add(t_strlst **lst, t_strlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		strlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

t_strlst	*strlst_new(t_ms *ms, int init_pos, int end_pos)
{
	t_strlst	*node;

	node = (t_strlst *)ft_calloc(1, sizeof(t_strlst));
	if (!node)
		return (NULL);
	node->str = ft_substr(ms->rline, init_pos, end_pos - init_pos + 1);
	node->index = init_pos;
	node->next = NULL;
	return (node);
}

/*
 * This function divides the ms->rline into str_lst tokens,
 * according to whether they are expandable or no 
 */
void	rline_to_lst(t_ms *ms)
{
	int	start;
	int	end;

	ms->str_lst = NULL;
	end = 0;
	start = 0;
	while (ms->rline[start])
	{
		if (ms->rline[start] == '$' && (ms->rline[start + 1] == '$' || ms->rline[start + 1] == '0' || ms->rline[start + 1] == '?'))
		{
			end += 2;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		else if (ms->rline[start] == '$' && ms->rline[start + 1] != ' ')
		{
			end++;
			while (ms->rline[end] && ms->rline[end] != ' ' && ms->rline[end] != '$' && ms->rline[end] != '"' && ms->rline[end] != '\'' && ms->rline[end] != '/' && ms->rline[end] != '?')
				end++;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		else
		{
			if(ms->rline[end] == '$')
				end++;
			while (ms->rline[end] && ms->rline[end] != '$')
				end++;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		start = end;
	}
}

void	free_str_lst(t_strlst *list)
{
	t_strlst	*next;

	next = list;
	while (list)
	{
		next = list->next;
		free (list->str);
		free (list);
		list = next;
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
 * the end of the list = null, need to test cd.
 */
void	expand_test(t_ms *ms)
{
	char		*expanded;
	char		*tmp;
	t_strlst	*tmp_strlst;

	rline_to_lst(ms);
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
