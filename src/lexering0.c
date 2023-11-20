
#include "../include/minishell.h"

void	count_pipes(t_ms *ms)
{
	char	*needle;
	size_t	i;
	size_t	j;
	int		pipe_count;

	needle = " | ";
	i = 0;
	pipe_count = 0;
	while (ms->rline[i] && i < ft_strlen(ms->rline))
	{
		j = 0;
		while (ms->rline[i + j] == needle[j] && i + j < ft_strlen(ms->rline))
		{
			if (needle[j + 1] == 0)
			{
				pipe_count++;
				i = i + j;
				break ;
			}
			j++;
		}
		i++;
	}
	ms->pipe_qty = pipe_count++;
}

void	create_shadow(t_ms *ms)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	ms->shadow = calloc(sizeof(char),  (ft_strlen(ms->rline) + 1));
	ft_memset(ms->shadow, '0', ft_strlen(ms->rline) + 1);
	while (ms->rline[i])
	{
		if (ms->rline[i] == '"' || ms->rline[i] == '\'')
		{
			quote = ms->rline[i];
			if (quote == '\'')
				ms->shadow[i++] = '1';
			else
				ms->shadow[i++] = '2';
			while ((ms->rline[i] && ms->rline[i] != quote) ||  (ms->rline[i] && ms->rline[i] == quote && ms->rline[i - 1] == '\\'))
			{
				if (quote == '\'')
					ms->shadow[i++] = '1';
				else
					ms->shadow[i++] = '2';
			}
			if (!ms->rline[i])
			{
				ft_printf(RED2"ERROR COMILLAS SIN CERRAR\n"RESET);
				ms->shadow[i] = 'E';
				break ;
			}
			if (quote == '\'')
				ms->shadow[i++] = '1';
			else
				ms->shadow[i++] = '2';
		}
		else
			i++;
	}
	ft_printf("SHADOW: %s\n", ms->shadow);
}

t_lexer_token	*lexer_token_last(t_lexer_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lexer_token_add(t_lexer_token **lst, t_lexer_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		lexer_token_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

t_lexer_token	*lexer_token_new(int init_pos, int end_pos)
{
	t_lexer_token	*node;

	if (end_pos < init_pos)
		return (NULL);
	printf(BLACK"CREO DE %i a %i\n"RESET, init_pos, end_pos);
	node = (t_lexer_token *)ft_calloc(1, sizeof(t_lexer_token));
	if (!node)
		return (NULL);
	node->init_pos = init_pos;
	node->end_pos = end_pos;
	node->next = NULL;
	return (node);
}

int	lexer_token_count(t_lexer_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void tokenize_rline(t_ms *ms)
{
	int		i;
	int		init;
	char	c;
	
	i = 0;
	printf("rline introducido: %s\n", ms->rline);
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
				i++;
			lexer_token_add(&ms->lexer_token, lexer_token_new(init, i - 1));
			if (c == '|')
				(lexer_token_last(ms->lexer_token))->tag_pipe = 1;
			else
			{
				(lexer_token_last(ms->lexer_token))->tag_redir += 1;
				if (c == '>')
					(lexer_token_last(ms->lexer_token))->tag_redir += 2;
				if (init != (i - 1))
					(lexer_token_last(ms->lexer_token))->tag_redir += 1;
			}
		}
		else if (ms->rline[i] == '"' || ms->rline[i] == '\'')
			{
				c = ms->rline[i];
				i++;
				while ((ms->rline[i] && ms->rline[i] != c) ||  (ms->rline[i] && ms->rline[i] == c && ms->rline[i - 1] == '\\'))
					i++;
				lexer_token_add(&ms->lexer_token, lexer_token_new(init + 1, i - 1));
				i++;
			}
		else
		{
			while (ms->rline[i] && ms->rline[i] != ' ' && ms->rline[i] != '\t' && ms->rline[i] != '"' && ms->rline[i] != '|' && ms->rline[i] != '<' && ms->rline[i] != '>')
				i++;
			lexer_token_add(&ms->lexer_token, lexer_token_new(init, i - 1));
		}
	}
	printf("TOKEN COUNT: %i\n", lexer_token_count(ms->lexer_token));
	while (ms->lexer_token)
		{
			if (ms->lexer_token->init_pos <= ms->lexer_token->end_pos)
				printf("PALABRA RECORTADA: "YELLOW"%s\n"GREEN"PIPE: %zu\nREDIR: %zu"RESET"\n", ft_substr(ms->rline, ms->lexer_token->init_pos, ms->lexer_token->end_pos - ms->lexer_token->init_pos + 1), ms->lexer_token->tag_pipe, ms->lexer_token->tag_redir);
			ms->lexer_token = ms->lexer_token->next;
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

void	rline_to_lst(t_ms *ms)
{
	int	start;
	int	end;

	ms->str_lst = NULL;
	end = 0;
	start = 0;
	while (ms->rline[start])
	{
		if (ms->rline[start] == '$' && ms->rline[start + 1] != ' ')
		{
			end++;
			while (ms->rline[end] && ms->rline[end] != ' ' && ms->rline[end] != '$' && ms->rline[end] != '"' && ms->rline[end] != '\'')
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

void	expand_lst(t_ms *ms)
{
	t_strlst	*tmp;
	t_strlst	*last;
	char		*var_str;

	tmp = ms->str_lst;
	while (tmp)
	{
		if (tmp->str[0] == '$' && tmp->index > 0 && ms->rline[tmp->index - 1] == '\\' && ms->shadow[tmp->index] != '1')
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

void	expand_test(t_ms *ms)
{
	char	*expanded;
	char	*tmp;

	rline_to_lst(ms);
	expand_lst(ms);
	expanded = ft_strdup("");
	while (ms->str_lst)
	{
		tmp = expanded;
		expanded = ft_strjoin(expanded, ms->str_lst->str);
		free (tmp);
		ms->str_lst = ms->str_lst->next;
	}
	free (ms->rline);
	ms->rline = expanded;
}