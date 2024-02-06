
#include "minishell.h"

int	check_pipes(t_ms *ms)
{
	t_parser_token	*ptmp;

	ptmp = ms->parser_token;
	if (ms->parser_token->lxr_list->tag_pipe)
		return (3);
	while (ptmp)
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

void	testing_parser_tokens(t_ms *ms)
{
	t_lexer_token	*tmp;
	t_parser_token	*ptmp;

	ptmp = ms->parser_token;
	printf("\n\nPARSER TOKENS: %i\n\n", parser_token_count(ms->parser_token));
	while (ptmp)
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

void	parsing_pipe_control(t_ms *ms)
{
	if (check_pipes(ms) == 1)
		error_handling(ERR_CNPP, 258);
	else if (check_pipes(ms) == 2)
		g_status = 258;
		//ft_putendl_fd(HCYN"> Is waiting for a command, and will the only one executed"RST, 1);
	else if (check_pipes(ms) == 3) //INITIAL PIPE
		error_handling(ERR_CNPP, 258);
	else
		parsing_to_executing(ms);
}

void	tokenize_parser(t_ms *ms)
{
	t_lexer_token	*tmp;

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
