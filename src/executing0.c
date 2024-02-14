
#include "minishell.h"

/* 
 * In Bash manual:
 *	[Simple Commands], the shell executes the command directly, without 
 *	invoking another program.
 *	[Pipelines], each command in a pipeline is executed in its own subshell.
 *	Builtin commands that are invoked as part of a pipeline are also executed 
 *	in a subshell environment. Changes made to the subshell environment cannot 
 *	affect the shell’s execution environment.
 *
 * if	-> execute way pipelines
 * else	-> execute simple command:
 * 		0 is command ## 1 is builtin, ## i'm thinkng 2 could be local var
 */
void	executing_token(t_ms *ms, t_parser_token *ptoken)
{
	if (ptoken_count(ms->parser_token) > 1)
	{
		if (parser_token_last(ms->parser_token)->token_id != ptoken->token_id)
			token_child(ms, ptoken);
		else
			token_last_child(ms, ptoken);
	}
	else
	{
		if (ptoken->tag == 1)
			execute_builtin(ms, ptoken, ptoken->lxr_list);
		else if (ptoken->tag == 2)
			execute_export(ms, ptoken->lxr_list);
		else
		{
			create_array(ms, ptoken->lxr_list);
			execute_simple(ms, ptoken);
		}
	}
}

/*
 * This function assigns ms->tube[0-1] to ms->ouput_fd/input_fd
 */
void	token_piping(t_ms *ms, t_parser_token *ptoken)
{
	(void)ms;
	if (ptoken->next && ptoken->next->lxr_list->tag_pipe)
		ptoken->output_fd = ms->tube[ptoken->token_id];
	if (ptoken->prev && ptoken->prev->lxr_list->tag_pipe)
		ptoken->input_fd = ms->tube[ptoken->token_id - 1];
}

/*
 * This function resets to default the fd 0 and 1
 */
void	reset_fds(t_ms *ms)
{
	dup2(ms->dflt_input, STDIN_FILENO);
	dup2(ms->dflt_output, STDOUT_FILENO);
}

/*
 * This function is the execution orchestrator
 */
void	parsing_to_executing(t_ms *ms)
{
	t_parser_token	*ptmp;

	if (ptoken_count(ms->parser_token) > 1)
		ms->tube = malloc(sizeof(int) * (ptoken_count(ms->parser_token) - 1));
	ptmp = ms->parser_token;
	set_signal_action(SIGEXE);
	while (ptmp)
	{
		if (ptmp->token_id % 2 == 1)
		{
			if (ptoken_count(ms->parser_token) > 1 && \
				ptmp->token_id != parser_token_last(ptmp)->token_id)
			{
				if ((int)ptmp->token_id != ptoken_count(ms->parser_token))
					pipe(&ms->tube[ptmp->token_id - 1]);
				token_piping(ms, ptmp);
			}
			if (check_redirs(ptmp))
				break ;
			executing_token(ms, ptmp);
		}
		ptmp = ptmp->next;
	}
	free_per_prompt(ms);
	reset_fds(ms);
}
