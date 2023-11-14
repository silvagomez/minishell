
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

	i = -1;
	quote = 0;
	ms->shadow = malloc(sizeof(char) * (ft_strlen(ms->prompt) + 1));
	ft_memset(ms->shadow, '1', ft_strlen(ms->prompt));
	while (ms->prompt[++i])
	{
		if (ms->prompt[i] == '"' || ms->prompt[i] == '\'')
		{
			quote = ms->prompt[i];
			ms->shadow[i] = '0';
			while (ms->prompt[++i] != quote)
				ms->shadow[i] = '0';
			ms->shadow[i] = '0';
		}
	}
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

	node = (t_token_pos *)malloc (sizeof(t_token_pos));
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
	ms->prompt[ft_strlen(ms->prompt) - 1] = 0;
	printf("Prompt introducido: %s\n", ms->prompt);
	ms->token_pos = NULL;
	while (ms->prompt[i])
	{
		while (ms->prompt[i] == 32 || ms->prompt[i] == '\t')
			i++;
		init = i;
		if (ms->prompt[i] == '"' || ms->prompt[i] == '\'')
			{
				c = ms->prompt[i];
				i++;
				while (ms->prompt[i] && ms->prompt[i] != c)
					i++;
				printf(BLACK"%cCREO DE %i a %i\n"RESET, c, init + 1, i - 1);
				token_pos_add(&ms->token_pos, token_pos_new(init + 1, i - 1));
			}
		else
		{
			while (ms->prompt[i] && ms->prompt[i] != 32)
				i++;
			printf(BLACK2"CREO DE %i a %i\n"RESET, init, i - 1);
			token_pos_add(&ms->token_pos, token_pos_new(init, i - 1));
		}
		i++;
	}
	printf("TOKEN COUNT: %i\n", token_pos_count(ms->token_pos));
	while (ms->token_pos)
		{
			if (ms->token_pos->init_pos <= ms->token_pos->end_pos)
				ft_printf("PALABRA RECORTADA: "YELLOW"%s\n"RESET, ft_substr(ms->prompt, ms->token_pos->init_pos, ms->token_pos->end_pos - ms->token_pos->init_pos + 1));
			ms->token_pos = ms->token_pos->next;
		}
}
