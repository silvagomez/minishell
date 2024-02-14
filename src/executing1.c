
#include "minishell.h"

void	execute_child(t_ms *ms, t_parser_token *ptoken)
{
	ptoken->pid = fork();
	if (ptoken->pid < 0)
		error_handling(ERR_FKFL, EXIT_FAILURE);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		if (!ms->pathlist)
			error_handling_exit(ERR_PATH, 127);
		check_command(ms, ptoken);
		check_ptoken_heredoc(ptoken);
		check_ptoken_input_heredoc(ptoken);
		check_ptoken_output_fd(ptoken);
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
	}
	else
		organize_fd_ptoken(ms, ptoken);
}

/*
 * Execution way of pipeline
 */
void	token_child(t_ms *ms, t_parser_token *ptoken)
{
	free(ms->cmd_array);
	ms->cmd_array = NULL;
	if (ptoken->tag == 0)
		create_array(ms, ptoken->lxr_list);
	execute_child(ms, ptoken);
}
