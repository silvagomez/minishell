
#include "minishell.h"

t_parser_token	*parser_token_last(t_parser_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	parser_token_add(t_parser_token **lst, t_parser_token *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		parser_token_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

int	parser_token_count(t_parser_token *lst)
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

t_parser_token	*parser_token_new(t_ms *ms, t_lexer_token *lexer_token)
{
	t_parser_token	*node;

	node = (t_parser_token *)ft_calloc(1, sizeof(t_parser_token));
	if (!node)
		return (NULL);
    node->lxr_list = lexer_token;
    node->lxr_list->prev = NULL;
	node->prev = parser_token_last(ms->parser_token);
	node->token_id = parser_token_count(ms->parser_token) + 1;
    node->output_fd = 1;
    node->input_fd = 0;
    node->next = NULL;
	node->default_stdin = dup (STDIN_FILENO);
	node->default_stdout = dup (STDOUT_FILENO);
	return (node);
}

int	check_pipes(t_ms *ms)
{
	t_parser_token	*ptmp;

	ptmp = ms->parser_token;
	while(ptmp)
	{
		if (ptmp->lxr_list->tag_pipe && ptmp->next && ptmp->next->lxr_list->tag_pipe)
			return (1);
		else if (ptmp->lxr_list->tag_pipe && ptmp->next == NULL)
			return (2);
		ptmp = ptmp->next;
	}
	return (0);
}

void tokenize_parser(t_ms *ms)
{
    t_lexer_token   *tmp;
    t_parser_token  *ptmp;

    tmp = ms->lexer_token;
    parser_token_add(&ms->parser_token, parser_token_new(ms, tmp));
    tmp = tmp->next;
    while (tmp)
    {
        if (tmp->tag_pipe)
        {
            tmp->prev->next = NULL;
            parser_token_add(&ms->parser_token, parser_token_new(ms, tmp));
			if (tmp->next && tmp->next->arg[0] != '|')
			{
				tmp = tmp->next;
				tmp->prev->next = NULL;
				parser_token_add(&ms->parser_token, parser_token_new(ms, tmp));
			}
        }
        tmp = tmp->next;
    }
    ptmp = ms->parser_token;
    printf("\n\nPARSER TOKENS: %i\n\n", parser_token_count(ms->parser_token));
    while(ptmp)
    {
        tmp = ptmp->lxr_list;
        printf(HMAG"%zu: "HBLU, ptmp->token_id);
        while (tmp)
        {
            printf("%s", tmp->arg);
            tmp = tmp->next;
            if (tmp)
                printf(" ");
        }
            printf(RST"\n\n");
        ptmp = ptmp->next;
    }
	if (check_pipes(ms) == 1)
		ft_putendl_fd(HRED"Errrrorrrrr double pipes continuous"RST, 2);
	else if (check_pipes(ms) == 2)
		ft_putendl_fd(HCYN"> Is waiting for a command, and will the only one executed"RST, 1);
	else
	{
		ptmp = ms->parser_token;
		while (ptmp)
		{
			if(ptmp->token_id % 2 == 1)
			{
				check_redirs(ptmp);
				execute_token(ms, ptmp);
			}
			ptmp = ptmp->next;
		}
	}
}
