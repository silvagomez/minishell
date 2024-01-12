
#include "minishell.h"

static const char	*g_builtin[8] = 
{
	"echo", 
	"cd", 
	"pwd", 
	"export", 
	"unset", 
	"env", 
	"exit",
	"declare"
};

size_t seek_equal(char *arg)
{
	if (ft_strchr(arg, '='))
		return (1);
	return (0);
}

void	remove_ltoken(t_parser_token *ptoken, size_t idx)
{
	t_lexer_token	*ltoken;

	while (ptoken->lxr_list->token_id != idx)
	{
		ltoken = ptoken->lxr_list;
		ptoken->lxr_list = ptoken->lxr_list->next;
		ptoken->lxr_list->prev = NULL;
		free(ltoken);
	}
}

//size_t	is_local_var(char *arg)
size_t	is_local_var(t_ms *ms, t_parser_token *ptoken)
{
	int				size;
	size_t			not_declare;

	(void)ms;
	t_lexer_token	*ltoken;

	size = lexer_token_count(ptoken->lxr_list);
	if (size == 1 && seek_equal(ptoken->lxr_list->arg))
	{
		if (ptoken->lxr_list->tag_double_q)
			return (0);
		else if (ptoken->lxr_list->tag_single_q)
			return (0);
		else
			return (2);
	}
	else
	{
		not_declare = 0;
		ltoken = ptoken->lxr_list;
		while (ltoken)
		{
			if (!seek_equal(ltoken->arg) || ltoken->tag_double_q || ltoken->tag_single_q)
			{
				not_declare = 1;
				break ;
			}
			ltoken = ltoken->next;
		}
		if (not_declare == 0)
			return (2);
		else if (ltoken->tag_double_q || ltoken->tag_single_q)
			return (0);
		else
		{
			remove_ltoken(ptoken, ltoken->token_id);
			if (is_builtin(ptoken->lxr_list))
				return (1);
			else
				return (0);
		}
	}
}

size_t is_command(t_ms *ms, t_lexer_token *ltoken)
{
	size_t	idx;
	char	*cmd;

	idx = -1;
	while (ms->pathlist[++idx])
	{
		cmd = ft_strjoin(ms->pathlist[idx], ltoken->arg);
		if (access(cmd, F_OK) == 0)
			return (free(cmd), ltoken->tag_program = 1, 1);
		free(cmd);
	}
	if (ms->pathlist[idx] == NULL)
	{
		if (access(ltoken->arg, F_OK) == 0)
			return (ltoken->tag_program = 1, 1);
		else
			return (0);
	}
	return (0);
}

size_t is_builtin(t_lexer_token *ltoken)
{
    int i;

    i = -1;
    while(++i < 8)
    {
        if (!ft_strncmp(ltoken->arg, g_builtin[i], ft_strlen(ltoken->arg) + 1))
		{
			ltoken->tag_builtin = 1;
            return (1);
		}
    }
	return (0);
}
size_t define_tag(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken)
{
	if (is_builtin(ltoken))
		return (1);
	if (is_command(ms, ltoken))
		return (0);
	return (is_local_var(ms, ptoken));
}

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

/*
 * node->tag = 0 program or cmd
 * node->tag = 1 built-in
 * node->tag = 2 local var
 */
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
	node->is_builtin = define_tag(ms, node, node->lxr_list);
	return (node);
}

int	check_pipes(t_ms *ms)
{
	t_parser_token	*ptmp;

	ptmp = ms->parser_token;
	if (ms->parser_token->lxr_list->tag_pipe)
		return (3);
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

/* void	first_child(t_pipex *ppx)
{
	close (ppx->tube[0]);
	dup2(ppx->tube[1], STDOUT_FILENO);
}

void	middle_child(t_pipex *ppx)
{
	dup2(ppx->tube[1], STDOUT_FILENO);
	close (ppx->tube[0]);
	close (ppx->tube[1]);
}

void	last_child(t_pipex *ppx)
{
	close (ppx->tube[1]);
	dup2(ppx->tube[0], STDIN_FILENO);
	set_output_fd(ppx);
}

void	father(t_pipex *ppx)
{
	close(ppx->tube[1]);
	waitpid(ppx->id, &ppx->z, WNOHANG);
	if (ppx->child < ppx->argc - 3)
	{
		dup2(ppx->tube[0], STDIN_FILENO);
	}
	if (ppx->child != ppx->argc - 3)
		close (ppx->tube[0]);
} */

void	token_piping(t_ms *ms, t_parser_token *ptoken)
{
	(void)ms;
	//printf("LXR LIST EMPIEZA CON: %s", ptoken->lxr_list->arg);
	if (ptoken->next && ptoken->next->lxr_list->tag_pipe)
	{
		//ft_putstr_fd(GRN"Hay pipe después."RST"\n", 2);
		ptoken->output_fd = ms->tube[ptoken->token_id];
	}
	if (ptoken->prev && ptoken->prev->lxr_list->tag_pipe)
	{
		//ft_putstr_fd(GRN"Hay pipe antes."RST"\n", 2);
		ptoken->input_fd = ms->tube[ptoken->token_id - 1];
	}
	//printf(GRN"INPUT FD VALE: %i\n", ptoken->input_fd);
	//printf("OUTPUT FD VALE: %i"RST"\n", ptoken->output_fd);
}

void reset_fds(t_ms *ms)
{
	dup2(ms->dflt_input, STDIN_FILENO);
	dup2(ms->dflt_output, STDOUT_FILENO);
}

void	testing_parser_tokens(t_ms *ms)
{
    t_lexer_token   *tmp;
    t_parser_token  *ptmp;

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
}

void	parsing_to_executing(t_ms *ms)
{
    t_parser_token  *ptmp;

	ptmp = ms->parser_token;
	if (parser_token_count(ms->parser_token) > 1)
		ms->tube = malloc(sizeof(int) * (parser_token_count(ms->parser_token) - 1));
	while (ptmp)
	{
		if(ptmp->token_id % 2 == 1)
		{
			if (parser_token_count(ms->parser_token) > 1)
			{
				pipe(&ms->tube[ptmp->token_id - 1]);
				token_piping(ms, ptmp);
			}
			check_redirs(ptmp);
			//execute_token(ms, ptmp);
			executing_token(ms, ptmp);
		}
		ptmp = ptmp->next;
	}
	reset_fds(ms);
}

void	parsing_pipe_control(t_ms *ms)
{
	if (check_pipes(ms) == 1)
		ft_putendl_fd(HRED"Errrrorrrrr double pipes continuous"RST, 2);
	else if (check_pipes(ms) == 2)
		ft_putendl_fd(HCYN"> Is waiting for a command, and will the only one executed"RST, 1);
	else if (check_pipes(ms) == 3)
		ft_putendl_fd(HRED"Errrrorrrrr Initial Pipe"RST, 2);
	else
		parsing_to_executing(ms);
}

void tokenize_parser(t_ms *ms)
{
    t_lexer_token   *tmp;

    tmp = ms->lexer_token;
    parser_token_add(&ms->parser_token, parser_token_new(ms, tmp));
    //tmp = tmp->next;
    while (tmp)
    {
        if (tmp->tag_pipe)
        {
			if (tmp->prev)
			{
            tmp->prev->next = NULL;
            parser_token_add(&ms->parser_token, parser_token_new(ms, tmp));
			}
			if (tmp->next && tmp->next->arg[0] != '|')
			{
				tmp = tmp->next;
				tmp->prev->next = NULL;
				parser_token_add(&ms->parser_token, parser_token_new(ms, tmp));
			}
        }
        tmp = tmp->next;
    }
	testing_parser_tokens(ms);
	parsing_pipe_control(ms);
}
