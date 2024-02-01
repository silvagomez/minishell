
#include "minishell.h"

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
				if ((int)ptmp->token_id != parser_token_count(ms->parser_token))
					pipe(&ms->tube[ptmp->token_id - 1]);
				token_piping(ms, ptmp);
			}
			check_redirs(ptmp);
			//execute_token(ms, ptmp);
			executing_token_idea2(ms, ptmp);
		}
		ptmp = ptmp->next;
	}
	reset_fds(ms);
}
