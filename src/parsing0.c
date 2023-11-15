
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
	while (ms->prompt[i] && i < ft_strlen(ms->prompt))
	{
		j = 0;
		while (ms->prompt[i + j] == needle[j] && i + j < ft_strlen(ms->prompt))
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
	ms->shadow = calloc(sizeof(char),  (ft_strlen(ms->prompt) + 1));
	ft_memset(ms->shadow, '0', ft_strlen(ms->prompt) + 1);
	while (ms->prompt[i])
	{
		if (ms->prompt[i] == '"' || ms->prompt[i] == '\'')
		{
			quote = ms->prompt[i];
			if (quote == '\'')
				ms->shadow[i++] = '1';
			else
				ms->shadow[i++] = '2';
			while (ms->prompt[i] != quote && ms->prompt[i])
			{
				if (quote == '\'')
					ms->shadow[i++] = '1';
				else
					ms->shadow[i++] = '2';
			}
			if (!ms->prompt[i])
			{
				ft_printf(RED2"ERROR COMILLAS SIN CERRAR: ESTOY EN CHAR=%i\n"RESET, ms->prompt[i]);
				ms->shadow[i] = 'E';
				break ;
			}
			if (quote == '\'')
				ms->shadow[i++] = '1';
			else
				ms->shadow[i++] = '2';
		}
		i++;
	}
	ft_printf("SHADOW: %s\n", ms->shadow);
}

t_token_pos	*token_pos_last(t_token_pos *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	token_pos_add(t_token_pos **lst, t_token_pos *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		token_pos_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

t_token_pos	*token_pos_new(int init_pos, int end_pos)
{
	t_token_pos	*node;

	if (end_pos < init_pos)
		return (NULL);
	printf(BLACK"CREO DE %i a %i\n"RESET, init_pos, end_pos);
	node = (t_token_pos *)ft_calloc(1, sizeof(t_token_pos));
	if (!node)
		return (NULL);
	node->init_pos = init_pos;
	node->end_pos = end_pos;
	node->next = NULL;
	return (node);
}

int	token_pos_count(t_token_pos *lst)
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

void tokenize_prompt(t_ms *ms)
{
	int		i;
	int		init;
	char	c;
	
	i = 0;
	printf("Prompt introducido: %s\n", ms->prompt);
	ms->token_pos = NULL;
	while (ms->prompt[i])
	{
		while (ms->prompt[i] == ' ' || ms->prompt[i] == '\t')
			i++;
		init = i;
		if (ms->prompt[i] == '|' || ms->prompt[i] == '>' || ms->prompt[i] == '<')
		{
			c = ms->prompt[i];
			while (ms->prompt[i] && ms->prompt[i] == c)
				i++;
			token_pos_add(&ms->token_pos, token_pos_new(init, i - 1));
			if (c == '|')
				(token_pos_last(ms->token_pos))->tag_pipe = 1;
			else
			{
				(token_pos_last(ms->token_pos))->tag_redir += 1;
				if (c == '>')
					(token_pos_last(ms->token_pos))->tag_redir += 2;
				if (init != (i - 1))
					(token_pos_last(ms->token_pos))->tag_redir += 1;
			}
		}
		else if (ms->prompt[i] == '"' || ms->prompt[i] == '\'')
			{
				c = ms->prompt[i];
				i++;
				while (ms->prompt[i] && ms->prompt[i] != c)
					i++;
				token_pos_add(&ms->token_pos, token_pos_new(init + 1, i - 1));
				i++;
			}
		else
		{
			while (ms->prompt[i] && ms->prompt[i] != ' ' && ms->prompt[i] != '\t' && ms->prompt[i] != '"' && ms->prompt[i] != '|' && ms->prompt[i] != '<' && ms->prompt[i] != '>')
				i++;
			token_pos_add(&ms->token_pos, token_pos_new(init, i - 1));
		}
	}
	printf("TOKEN COUNT: %i\n", token_pos_count(ms->token_pos));
	while (ms->token_pos)
		{
			if (ms->token_pos->init_pos <= ms->token_pos->end_pos)
				printf("PALABRA RECORTADA: "YELLOW"%s\n"GREEN"PIPE: %zu\nREDIR: %zu"RESET"\n", ft_substr(ms->prompt, ms->token_pos->init_pos, ms->token_pos->end_pos - ms->token_pos->init_pos + 1), ms->token_pos->tag_pipe, ms->token_pos->tag_redir);
			ms->token_pos = ms->token_pos->next;
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
	node->str = ft_substr(ms->prompt, init_pos, end_pos - init_pos + 1);
	node->index = init_pos;
	node->next = NULL;
	return (node);
}

void	prompt_to_lst(t_ms *ms)
{
	int	start;
	int	end;

	ms->str_lst = NULL;
	end = 0;
	start = 0;
	while (ms->prompt[start])
	{
		if (ms->prompt[start] == '$' && ms->prompt[start + 1] != ' ')
		{
			end++;
			while (ms->prompt[end] && ms->prompt[end] != ' ' && ms->prompt[end] != '$' && ms->prompt[end] != '"' && ms->prompt[end] != '\'')
				end++;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		else
		{
			if(ms->prompt[end] == '$')
				end++;
			while (ms->prompt[end] && ms->prompt[end] != '$')
				end++;
			strlst_add(&ms->str_lst, strlst_new(ms, start, end - 1));
		}
		start = end;
	}
}

void	expand_lst(t_ms *ms)
{
	t_strlst	*tmp;
	char		*var_str;

	tmp = ms->str_lst;
	while (tmp)
	{
		if (tmp->str[0] == '$' && ms->shadow[tmp->index] != '1' && ms->prompt[tmp->index + 1] != ' ' && ms->prompt[tmp->index + 1] && ms->prompt[tmp->index + 1] != '"')
		{
			if (getenv(tmp->str + 1))
				var_str = ft_strdup(getenv(tmp->str + 1));
			else
				var_str = ft_strdup("");
			free (tmp->str);
			tmp->str = var_str;
		}
		tmp = tmp->next;
	}
}

void	expand_test(t_ms *ms)
{
	char	*expanded;
	char	*tmp;

	prompt_to_lst(ms);
	expand_lst(ms);
	expanded = ft_strdup("");
	while (ms->str_lst)
	{
		tmp = expanded;
		expanded = ft_strjoin(expanded, ms->str_lst->str);
		free (tmp);
		ms->str_lst = ms->str_lst->next;
	}
	free (ms->prompt);
	ms->prompt = expanded;
}